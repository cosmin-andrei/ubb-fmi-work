const Koa = require('koa');
const app = new Koa();
const server = require('http').createServer(app.callback());
const WebSocket = require('ws');
const wss = new WebSocket.Server({server});
const Router = require('koa-router');
const cors = require('koa-cors');
const bodyparser = require('koa-bodyparser');

app.use(bodyparser());
app.use(cors());

app.use(async function (ctx, next) {
  const start = new Date();
  await next();
  const ms = new Date() - start;
  console.log(`${ctx.method} ${ctx.url} - ${ms}ms`);
});

app.use(async (ctx, next) => {
  await new Promise(resolve => setTimeout(resolve, 2000));
  await next();
});

const spaces = Array.from(Array(30).keys())
  .map((id, index) => ({ id, number: `s${id}`, takenBy: id % 3 === 0 ? '' : `u${index % 3}` }));

const broadcast = data =>
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      console.log('broadcast', data);
      client.send(JSON.stringify(data));
    }
  });

let index = 4;

setInterval(() => {
  index += 1;
  if (index >= spaces.length) {
    index = 4;
  }
  if (spaces[index].takenBy) {
    spaces[index].takenBy = '';
  } else {
    spaces[index].takenBy = `u${index % 3}`;
  }
  broadcast(spaces[index]);
}, 10000);

const router = new Router();
router.get('/space', ctx => {
  ctx.response.body = spaces;
  ctx.response.status = 200;
});

router.put('/space/:id', ctx => {
  const space = ctx.request.body;
  const id = parseInt(ctx.params.id);
  const index = spaces.findIndex(space => space.id === id);
  if (id !== space.id || index === -1) {
    ctx.response.body = { text: 'Space not found' };
    ctx.response.status = 400;
  } else if (space.status === spaces[index].status) {
    ctx.response.body = { text: 'Conflict, cannot update status' };
    ctx.response.status = 409;
  } else {
    Object.assign(spaces[index], space);
    ctx.response.body = spaces[index];
    ctx.response.status = 200;
  }
});

app.use(router.routes());
app.use(router.allowedMethods());

server.listen(3000);
