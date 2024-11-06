<?php
$conn = mysqli_connect("localhost", "root", "","lab6");
if (!$conn) {
    die('Could not connect: ' . mysqli_error($conn));
}
$name = $_POST["name"];
$phone = $_POST["phone"];
$email = $_POST["email"];
$id = $_POST["id"];
$sql =  "UPDATE persons2 SET Name = '" .$name ."', Phone = '" .$phone ."', Email = '" .$email ."' WHERE id = '".$id ."';";
if (mysqli_query($conn, $sql)) {
    echo "Updated.";
} else {
    echo "Error: " . mysqli_error($conn);
}

mysqli_close($conn);
