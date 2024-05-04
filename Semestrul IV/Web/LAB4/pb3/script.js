var valori = [];
var tile_ids = [];
var flipped = 0;
var variabile = ['1', '1', '2', '2', '3', '3', '4', '4', '5', '5', '6', '6'];

Array.prototype.tile_shuffle = function() {
  var i = this.length,
    j, temp;
  while (--i > 0) {
    j = Math.floor(Math.random() * (i + 1));
    temp = this[j];
    this[j] = this[i];
    this[i] = temp;
  }
}

function FlipTile(tile, val) {
  if (tile.innerHTML == "" && valori.length < 2) {
    tile.style.background = '#CCFBFE';
    tile.innerHTML =  val;
    if (valori.length == 0) {
      valori.push(val);
      tile_ids.push(tile.id);
    } else if (valori.length == 1) {
      valori.push(val);
      tile_ids.push(tile.id);
      if (valori[0] == valori[1]) {
        flipped += 2;
        valori = [];
        tile_ids = [];
        if (flipped == variabile.length) {
          alert("Game over!");
          document.getElementById('game').innerHTML = "";
          newPatrat();
        }
      } else {
        function reIntoarcere() {
          var tile_1 = document.getElementById(tile_ids[0]);
          var tile_2 = document.getElementById(tile_ids[1]);
          tile_1.style.background = '';
          tile_1.innerHTML = "";
          tile_1.classList.remove('error');
          tile_2.style.background = '';
          tile_2.innerHTML = "";
          tile_2.classList.remove('error');
          valori = [];
          tile_ids = [];
        }
        setTimeout(reIntoarcere, 700);
      }
    }
  }
}

function newPatrat() {
  flipped = 0;
  var output = '';
  variabile.tile_shuffle();
  for (var i = 0; i < variabile.length; i++) {
    output += '<div id="tile_' + i + '" onclick="FlipTile(this,\'' + variabile[i] + '\')"></div>';
  }
  document.getElementById('game').innerHTML = output;
}

window.onload = function() {
  newPatrat();
};
