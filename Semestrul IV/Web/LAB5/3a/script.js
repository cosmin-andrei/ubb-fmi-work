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
    if (tile.html() == "" && valori.length < 2) {
        tile.css('background', '#CCFBFE');
        tile.html(val);
        if (valori.length == 0) {
            valori.push(val);
            tile_ids.push(tile.attr('id'));
        } else if (valori.length == 1) {
            valori.push(val);
            tile_ids.push(tile.attr('id'));
            if (valori[0] == valori[1]) {
                flipped += 2;
                valori = [];
                tile_ids = [];
                if (flipped == variabile.length) {
                    alert("Game over!");
                    $('#game').html("");
                    newPatrat();
                }
            } else {
                function reIntoarcere() {
                    var tile_1 = $('#' + tile_ids[0]);
                    var tile_2 = $('#' + tile_ids[1]);
                    tile_1.css('background', '');
                    tile_1.html("");
                    tile_2.css('background', '');
                    tile_2.html("");
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
        output += '<div class="tile" id="tile_' + i + '"></div>';
    }
    $('#game').html(output);
}

$(document).ready(function() {
    newPatrat();
    $(document).on('click', '.tile', function() {
        var id = $(this).attr('id');
        var index = parseInt(id.replace('tile_', ''));
        FlipTile($(this), variabile[index]);
    });
});
