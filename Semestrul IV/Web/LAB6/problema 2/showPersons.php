<?php
$con = mysqli_connect("localhost", "root", "","lab6");
if (!$con) {
    die('Could not connect: ' . mysqli_error($con));
}

$noPage = $_GET["page"];
$pageLimit = 3;
$result = mysqli_query($con, "SELECT * FROM person limit " .$noPage ."," . $pageLimit .";");

echo "<tr><th>Last name</th><th>First name</th><th>Phone</th><th>Email</th></tr>";
while($row = mysqli_fetch_array($result)){
    echo "<tr><td>" .$row["last_name"] ."</td><td>" .$row["first_name"] ."</td><td>".$row["phone"] ."</td><td>" .$row["email"] . "</td></tr>";
}
mysqli_close($con);
