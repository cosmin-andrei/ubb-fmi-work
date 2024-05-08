var empty, dim = 3;

$(document).ready(function(){
  generateTable();
  $(document).keydown(checkKey);
});

function generateTable() {
  var numbers = generateNumbers(dim * dim);
  var output = "";

  for (let i = 0; i < dim; i++) {
    output += '<tr>';
    for (let j = 0; j < dim; j++) {
      output += `<td id='${i * dim + j}' ></td>`;
    }
    output += '</tr>';
  }
  $("#tbl").html(output);

  $("#tbl td").each(function(index){
    let elem = numbers.pop();
    if (elem != dim * dim) {
      $(this).text(elem);
    } else {
      empty = $(this).attr('id');
    }
  });
}

function swap(id1, id2) {
  let aux = $("#" + id1).text();
  $("#" + id1).text($("#" + id2).text());
  $("#" + id2).text(aux);
  empty = id2; // Actualizăm poziția casuței goale
}

function checkKey(e) {
  e = e || window.event;

  if (e.keyCode == '38') {
    if (empty - dim >= 0)
      swap(empty, empty - dim);
    else
      alert('Nu in sus');
  } else if (e.keyCode == '40') {
    if (empty + dim < dim * dim)
      swap(empty, empty + dim);
    else
      alert('Nu in jos');
  } else if (e.keyCode == '37') {
    if (empty % dim != 0)
      swap(empty, empty - 1);
    else
      alert('Nu in stanga');
  } else if (e.keyCode == '39') {
    if (empty % dim != dim - 1)
      swap(empty, empty + 1);
    else
      alert('Nu in dreapta');
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
