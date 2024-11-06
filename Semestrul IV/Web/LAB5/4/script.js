$(document).ready(function () {

    $("table").on("click", "tr th", function () {

        var column = $(this).index();
        var $table = $(this).closest("table");
        var $tbody = $table.find("tbody");
        var rows = $tbody.find("tr").get();
        var sortOrder = $(this).hasClass("ascendent") ? "descendent" : "ascendent";

        for (var i = 1; i < rows.length - 1; i++) {
            for(var j = i + 1; j < rows.length; j++) {

                var firstValue = $(rows[i]).find("td").eq(column).text();
                var secondValue = $(rows[j]).find("td").eq(column).text();

                if((sortOrder === "ascendent" && firstValue > secondValue) || (sortOrder === "descendent" && firstValue < secondValue)) {
                    var temp = rows[i];
                    rows[i] = rows[j];
                    rows[j] = temp;
                }

            }
        }

        $tbody.empty();
        $tbody.append(rows);
        $(this).toggleClass("ascendent").toggleClass("descendent");

    });

});
