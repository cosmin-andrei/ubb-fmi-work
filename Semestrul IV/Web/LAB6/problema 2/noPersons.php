<?php
$con = mysqli_connect("localhost", "root", "","lab6");
if (!$con) {
    die('Could not connect: ' . mysqli_error($con));
}

$noPage = $_GET["page"];
//$noPage = 0;
$pageLimit = 3;
$result = mysqli_query($con, "SELECT * FROM person limit " .$noPage ."," . $pageLimit .";");

echo $result->num_rows;

mysqli_close($con);
