var valori = [];
var tile_ids = [];
var flipped = 0;
var variabile = [
    'img/bufny.jpg', 'img/bufny.jpg', 'img/berinde.jpg', 'img/berinde.jpg',
    'img/gabi.jpg', 'img/gabi.jpg', 'img/suciu.jpg', 'img/suciu.jpg', 'img/vancea.jpg',
    'img/vancea.jpg', 'img/pop.jpg', 'img/pop.jpg'
];

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
    if ($(tile).html() == "" && valori.length < 2) {
        $(tile).css("background", "#CCFBFE");
        $(tile).html('<img src="' + val + '" style="width: 100%; height: 100%;">');
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
                    $("#game").empty();
                    newPatrat();
                }
            } else {
                function reIntoarcere() {
                    var tile_1 = document.getElementById(tile_ids[0]);
                    var tile_2 = document.getElementById(tile_ids[1]);
                    $(tile_1).css("background", "");
                    $(tile_1).html("");
                    $(tile_2).css("background", "");
                    $(tile_2).html("");
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
        output += '<div id="tile_' + i + '" class="tile"></div>';
    }
    $("#game").html(output);
    $(".tile").click(function() {
        var index = $(this).index();
        FlipTile(this, variabile[index]);
    });
}

$(document).ready(function() {
    newPatrat();
});