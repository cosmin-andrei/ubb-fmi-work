<?php
$con = mysqli_connect("localhost", "root", "", "lab6");
if (!$con) {
    die('Could not connect: ' . mysqli_error($con));
}

$result = mysqli_query($con, "SELECT DISTINCT departure FROM routes");
$options = "";
while ($row = mysqli_fetch_array($result)) {
    $options .= "<option value='" . $row['departure'] . "'>" . $row['departure'] . "</option>";
}
echo $options;

mysqli_close($con);

