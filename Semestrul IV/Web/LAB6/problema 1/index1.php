<!DOCTYPE html>
<html lang="ro">
<head>
    <script src="https://code.jquery.com/jquery-2.0.3.js"></script>
    <script>
        $(document).ready(function(){
            $.ajax({
                type: "GET",
                url: "showDepartures.php",
                success: function(data) {
                    $("#departures").html(data);
                }
            });

            $('#departures').change(function(){
                let value = $(this).val();
                if (value) {
                    $.ajax({
                        type: "GET",
                        url: "showArrivals.php",
                        data: { name: value },
                        success: function(data) {
                            $('#arrivals').html(data);
                            $('#arrivalsResult').html('<p>' + data + '</p>');
                        }
                    });
                } else {
                    $('#arrivals').html('<option>(none)</option>');
                }
            });

        });
    </script>
    <title>Pb1</title>
</head>
<body>

<span>
    <label>
        Departures
        <select id="departures" multiple size="6">
        </select>
    </label>
</span>
<br>
<span>
    <label>
        Arrivals
        <select id="arrivals" multiple size="6">
            <option>(none)</option>
        </select>
    </label>
</span>

<div id="arrivalsResult"></div>

</body>
</html>
