function sortTable(n, x) {
  var table, rows, switching, i, j, x, shouldSwitch, dir, switchcount = 0,
    copie, idTable;
  idTable = x.parentNode.parentNode.parentNode.id;
  table = document.getElementById(idTable);
  switching = true;

  dir = "asc";
  while (switching) {

    switching = false;

    x = table.rows[n].cells
    for (i = 1; i < (x.length - 1); i++) {
      shouldSwitch = false;
      if (dir == "asc") {

        if (x[i].innerHTML.toLowerCase() > x[i + 1].innerHTML.toLowerCase()) {
          shouldSwitch = true;
          break;
        }
      } else if (dir == "desc") {
        if (x[i].innerHTML.toLowerCase() < x[i + 1].innerHTML.toLowerCase()) {
          shouldSwitch = true;
          break;
        }
      }
    }


    if (shouldSwitch) {
      for (j = 0; j < table.rows.length; j++) {
        copie = table.rows[j].cells[i].innerHTML
        table.rows[j].cells[i].innerHTML = table.rows[j].cells[i + 1].innerHTML;
        table.rows[j].cells[i + 1].innerHTML = copie;
      }


      switching = true;
      switchcount++;
    } else {
      if (switchcount == 0 && dir == "asc") {
        dir = "desc";
        switching = true;
      }
    }
  }
}
function sortSecondTable(n, x) {
  var table, rows, switching, i, shouldSwitch, dir, switchcount = 0,
    idTable;
  idTable = x.parentNode.parentNode.parentNode.id;
  table = document.getElementById(idTable);
  switching = true;

  dir = "asc";
  while (switching) {

    switching = false;

    rows = table.rows;
    for (i = 1; i < (rows.length - 1); i++) {
      shouldSwitch = false;
      var xRow = rows[i].getElementsByTagName("td")[n];
      var yRow = rows[i + 1].getElementsByTagName("td")[n];
      if (dir == "asc") {
        if (xRow.innerHTML.toLowerCase() > yRow.innerHTML.toLowerCase()) {
          shouldSwitch = true;
          break;
        }
      } else if (dir == "desc") {
        if (xRow.innerHTML.toLowerCase() < yRow.innerHTML.toLowerCase()) {
          shouldSwitch = true;
          break;
        }
      }
    }

    if (shouldSwitch) {
      rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
      switching = true;
      switchcount++;
    } else {
      if (switchcount == 0 && dir == "asc") {
        dir = "desc";
        switching = true;
      }
    }
  }
}
