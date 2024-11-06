<?php
$conn = mysqli_connect("localhost", "root", "","lab7");
if (!$conn) {
    die('Could not connect: ' . mysqli_error($conn));
}

$pageLimit = isset($_GET["produse"]) ? intval($_GET["produse"]) : 5; // Default value if not set
$pageNo = isset($_GET["noPage"]) ? intval($_GET["noPage"]) : 0;

if ($pageLimit <= 0) {
    die('Null or invalid error on a page');
}

$pattern = '/^[0-9]{1,30}$/';
if (!preg_match($pattern, $pageLimit)) {
    header("Location: http://localhost/pb2/");
    exit;
}

$offset = $pageNo * $pageLimit;
$sql = "SELECT * FROM produse LIMIT $offset, $pageLimit";
$result = mysqli_query($conn, $sql);

echo "<form action='showProduse.php' method='GET'>
    <input type='hidden' name='noPage' value='0'>
    <select name='produse'>
        <option value='1'>1</option>
        <option value='2'>2</option>
        <option value='3'>3</option>
        <option value='4'>4</option>
        <option value='5'>5</option>
    </select>
    <input type='submit' value='Send'>
</form>";
echo "<hr>";
echo "<table border='1'><tr><th>Denumire</th><th>Categorie</th><th>Pret</th><th>Stoc</th><th>Descriere</th></tr>";

while($row = mysqli_fetch_array($result)){
    echo "<tr><td>" . $row["Nume_Produs"] . "</td><td>" . $row["Categorie"] . "</td><td>" . $row["Pret"] . "</td>";
    echo "<td>" . $row["Stoc"] . "</td><td>" . $row["Descriere"] . "</td></tr>";
}
echo "</table>";
echo "<hr>";

echo "<table><tr><td>";
$existaPrev = $pageNo > 0;

echo "<form action='showProduse.php' method='GET'>";
echo "<input type='hidden' name='noPage' value='" . ($pageNo - 1) . "'>";
echo "<input type='hidden' name='produse' value='" . $pageLimit . "'>";
if (!$existaPrev) {
    echo "<input type='submit' value='Prev' disabled>";
} else {
    echo "<input type='submit' value='Prev'>";
}
echo "</form></td><td>";

$existaNext = false;
$sql = "SELECT * FROM produse LIMIT " . ($offset + $pageLimit) . ", 1";
$result = mysqli_query($conn, $sql);
if (mysqli_fetch_array($result)) {
    $existaNext = true;
}

echo "<form action='showProduse.php' method='GET'>";
echo "<input type='hidden' name='noPage' value='" . ($pageNo + 1) . "'>";
echo "<input type='hidden' name='produse' value='" . $pageLimit . "'>";
if ($existaNext) {
    echo "<input type='submit' value='Next'>";
} else {
    echo "<input type='submit' value='Next' disabled>";
}
echo "</form></td></tr></table>";

mysqli_close($conn);

