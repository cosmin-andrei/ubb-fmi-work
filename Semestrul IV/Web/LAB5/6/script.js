var emptyRow, emptyColumn, dim = 3;

$(document).ready(function(){
  $(document).keydown(checkKey);
});

function generateTable() {
  var numbers = generateNumbers(dim * dim);
  var output = "";

  for (let i = 0; i < dim; i++) {
    output += '<tr>';
    for (let j = 0; j < dim; j++) {
      output += `<td id='cell_${i}_${j}' ></td>`;
    }
    output += '</tr>';
  }
  $("#tbl").html(output);

  $("#tbl td").each(function(index){
    let elem = numbers.pop();
    if (elem != dim * dim) {
      $(this).text(elem);
    } else {
      emptyRow = $(this).parent().index();
      emptyColumn = $(this).index();
    }
  });
}

function swap(row1, col1, row2, col2) {
  let cell1 = $(`#cell_${row1}_${col1}`);
  let cell2 = $(`#cell_${row2}_${col2}`);
  let aux = cell1.text();
  cell1.text(cell2.text());
  cell2.text(aux);
}

function checkKey(e) {
  e = e || window.event;

  if (e.keyCode == '38') {
    if (emptyRow > 0) {
      swap(emptyRow, emptyColumn, emptyRow - 1, emptyColumn);
      emptyRow--;
    } else {
      alert('Nu sus');
    }
  } else if (e.keyCode == '40') {
    if (emptyRow < dim - 1) {
      swap(emptyRow, emptyColumn, emptyRow + 1, emptyColumn);
      emptyRow++;
    } else {
      alert('Nu jos');
    }
  } else if (e.keyCode == '37') {
    if (emptyColumn > 0) {
      swap(emptyRow, emptyColumn, emptyRow, emptyColumn - 1);
      emptyColumn--;
    } else {
      alert('Nu stanga');
    }
  } else if (e.keyCode == '39') {
    if (emptyColumn < dim - 1) {
      swap(emptyRow, emptyColumn, emptyRow, emptyColumn + 1);
      emptyColumn++;
    } else {
      alert('Nu dreapta');
    }
  }
}

function shuffle(a) {
  for (let i = a.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [a[i], a[j]] = [a[j], a[i]];
  }
  return a;
}

function generateNumbers(n) {
  array = [];
  for (let i = 1; i <= n; i++) {
    array.push(i);
  }
  shuffle(array);
  return array;
}
