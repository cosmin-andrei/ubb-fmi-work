<?php
$con = mysqli_connect("localhost", "root", "", "lab6");
if (!$con) {
    die('Could not connect: ' . mysqli_error($con));
}

$id = $_GET["id"];
$result = mysqli_query($con, "SELECT name, phone, email FROM persons2 WHERE id=" . $id);

$row = mysqli_fetch_array($result);
echo "<label>Name: </label>";
echo "<input type='text' name='name' value = '" . $row["name"] . "'>";
echo "<br>";
echo "<label>Phone: </label>";
echo "<input type='text' name='phone' value = '" . $row["phone"] . "'>";
echo "<br>";
echo "<label>Email: </label>";
echo "<input type='text' name='email' value = '" . $row["email"] . "'>";
echo "<br>";
echo "<input id='bttn' type='submit' value ='Save' disabled>";
mysqli_close($con);