
const express = require('express');
const http = require('http');
const path = require('path');
const socketIo = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = new socketIo.Server(server);

app.use(express.static(path.join(__dirname, '../public')));

server.listen(3000, () => {
    console.log("Server running at http://localhost:3000");

    io.on('connection', client => {
        console.log(`Client connected: ${client.id}`);

        client.on('disconnect', () => onRemovePlayer(client));
        client.on('new player', (player) => onNewPlayer(client, player));
        client.on('move player', (player) => onMovePlayer(client, player));
        client.on('collect orb', () => onCollectOrb(client));
    });
});

class Player {
    constructor(startX, startY, startAngle) {
        this.x = startX;
        this.y = startY;
        this.angle = startAngle;
        this.score = 0;
    }
}

const players = {};

const onRemovePlayer = client => {
    console.log(`Removing player: ${client.id}`);
    const removePlayer = players[client.id];
    if (!removePlayer) return;
    delete players[client.id];
    io.emit('remove player', removePlayer);
};

const onNewPlayer = (ioClient, player) => {
    const newPlayer = new Player(player.x, player.y, player.angle);
    newPlayer.id = ioClient.id;
    players[newPlayer.id] = newPlayer;

    ioClient.broadcast.emit('new player', newPlayer);

    Object.values(players).forEach(p => {
        if (p.id !== newPlayer.id) {
            ioClient.emit('new player', p);
        }
    });
};

const onMovePlayer = (ioClient, player) => {
    const movePlayer = players[ioClient.id];
    if (!movePlayer) return;
    Object.assign(movePlayer, player);
    ioClient.broadcast.emit('move player', movePlayer);
};

const onCollectOrb = (ioClient) => {
    const player = players[ioClient.id];
    if (!player) return;
    player.score++;
    io.emit('update score', { id: player.id, score: player.score });
};
