<?php

include 'config.php';

$conn = new mysqli($db_config['servername'], $db_config['username'], $db_config['password'], $db_config['dbname']);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $id = $_POST['id'];
    if (isset($_POST['approve'])) {
        if ($conn->query("UPDATE comments SET approved = 1 WHERE id = $id") === TRUE) {
            echo "Approved.";
        } else {
            echo "Error: " . $conn->error;
        }
    } elseif (isset($_POST['reject'])) {
        if ($conn->query("DELETE FROM comments WHERE id = $id") === TRUE) {
            echo "Rejected.";
        } else {
            echo "Error: " . $conn->error;
        }
    }
}

$conn->close();
