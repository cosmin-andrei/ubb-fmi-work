<?php

include 'config.php';

$conn = new mysqli($db_config['servername'], $db_config['username'], $db_config['password'], $db_config['dbname']);



if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}


$name = $_POST['name'];
$comment = $_POST['comment'];

$sql = "INSERT INTO comments (name, comment, approved) VALUES ('$name', '$comment', 0)";

if ($conn->query("INSERT INTO comments (name, comment, approved) VALUES ('$name', '$comment', 0)") === TRUE) {
    echo "OK. Wait for approve.";
} else {
    echo "Error: " . $conn->error;
}

$conn->close();

