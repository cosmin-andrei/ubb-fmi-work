<?php
$con = mysqli_connect("localhost", "root", "","lab6");
if (!$con) {
    die('Could not connect: ' . mysqli_error($con));
}

$result = mysqli_query($con, "SELECT arrival FROM routes WHERE departure = '" .$_GET['name'] ."'");

while($row = mysqli_fetch_array($result)){
    echo "<option value=" . $row[0] . ">" . $row[0] . "</option>";
}
mysqli_close($con);