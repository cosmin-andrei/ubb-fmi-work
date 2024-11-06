<?php
$conn = mysqli_connect("localhost", "root", "", "lab6");
if (!$conn) {
    die('Could not connect: ' . mysqli_connect_error());
}

$items = isset($_GET["items"]) ? $_GET["items"] : [];

function getItem($i): string
{
    switch ($i) {
        case 0:
            return "producator";
        case 1:
            return "procesor";
        case 2:
            return "memorie";
        case 3:
            return "capacitatehdd";
        case 4:
            return "placavideo";
        default:
            return "";
    }
}

$condition = "";
$params = [];
$types = "";

for ($i = 0; $i < count($items); $i++) {
    $item = getItem($i);
    if ($items[$i] != '' && $item != '') {
        if ($condition == '') {
            $condition = "WHERE ";
        } else {
            $condition .= "AND ";
        }
        $condition .= "$item = ? ";
        $params[] = $items[$i];
        $types .= "s"; // assuming all columns are strings
    }
}

$sql = "SELECT * FROM products " . $condition;
$stmt = mysqli_prepare($conn, $sql);

if ($stmt && !empty($params)) {
    mysqli_stmt_bind_param($stmt, $types, ...$params);
    mysqli_stmt_execute($stmt);
    $result = mysqli_stmt_get_result($stmt);
} else {
    $result = mysqli_query($conn, $sql);
}

echo "<table>";
echo "<tr><th>Producator</th><th>Procesor</th><th>Memorie</th><th>CapacitateHDD</th><th>PlacaVideo</th></tr>";
while ($row = mysqli_fetch_assoc($result)) {
    echo "<tr><td>" . htmlspecialchars($row["producator"]) . "</td><td>" . htmlspecialchars($row["procesor"]) . "</td><td>" . htmlspecialchars($row["memorie"]) . "</td>";
    echo "<td>" . htmlspecialchars($row["capacitatehdd"]) . "</td><td>" . htmlspecialchars($row["placavideo"]) . "</td></tr>";
}
echo "</table>";

mysqli_close($conn);

