$(document).ready(function() {
  $('.sortable th').click(function() {
    var columnIndex = $(this).index();
    var $table = $(this).closest('table');
    var sortFunction = $table.attr('id') === 'secondTable' ? sortSecondTable : sortTable;
    sortFunction(columnIndex, this);
  });
});

function sortTable(n, x) {
  var $table = $(x).closest('table');
  var $rows = $table.find('tr').not(':first');
  var switching = true;
  var dir = "asc";

  while (switching) {
    switching = false;
    var $cells = $rows.find('td:nth-child(' + (n + 1) + ')');

    $cells.each(function(i) {
      var $this = $(this);
      var $next = $this.next();

      if (dir == "asc") {
        if ($this.text().toLowerCase() > $next.text().toLowerCase()) {
          $this.closest('tr').insertBefore($next.closest('tr'));
          switching = true;
          return false; // break loop
        }
      } else if (dir == "desc") {
        if ($this.text().toLowerCase() < $next.text().toLowerCase()) {
          $this.closest('tr').insertBefore($next.closest('tr'));
          switching = true;
          return false; // break loop
        }
      }
    });

    if (!switching && dir == "asc") {
      dir = "desc";
      switching = true;
    }
  }
}

function sortSecondTable(n, x) {
  var $table = $(x).closest('table');
  var $rows = $table.find('tr').not(':first');
  var switching = true;
  var dir = "asc";

  while (switching) {
    switching = false;
    $rows.each(function(i) {
      var $thisRow = $(this);
      var $nextRow = $rows.eq(i + 1);

      var $thisCell = $thisRow.find('td').eq(n);
      var $nextCell = $nextRow.find('td').eq(n);

      if (dir == "asc") {
        if ($thisCell.text().toLowerCase() > $nextCell.text().toLowerCase()) {
          $thisRow.insertBefore($nextRow);
          switching = true;
          return false; // break loop
        }
      } else if (dir == "desc") {
        if ($thisCell.text().toLowerCase() < $nextCell.text().toLowerCase()) {
          $thisRow.insertBefore($nextRow);
          switching = true;
          return false; // break loop
        }
      }
    });

    if (!switching && dir == "asc") {
      dir = "desc";
      switching = true;
    }
  }
}
