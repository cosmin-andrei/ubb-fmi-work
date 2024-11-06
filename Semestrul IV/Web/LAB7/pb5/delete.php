<?php
session_start();
if (!isset($_SESSION['user_logged']) || $_SESSION['user_logged'] !== true) {
    header("Location: login.php");
    exit();
}

if ($_SERVER["REQUEST_METHOD"] == "GET" && isset($_GET["image_id"])) {
    include 'config.php';
    $conn = new mysqli($db_config['servername'], $db_config['username'], $db_config['password'], $db_config['dbname']);
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $image_id = $_GET["image_id"];
    $sql = "SELECT image_name FROM images WHERE id = $image_id";
    $result = $conn->query($sql);
    if ($result->num_rows == 1) {
        $row = $result->fetch_assoc();
        $image_name = $row["image_name"];

        $conn->query("DELETE FROM images WHERE id = $image_id");

        $upload_dir = "uploads/";
        $file_path = $upload_dir . $image_name;
        if (file_exists($file_path)) {
            unlink($file_path);
        }
    }

    $conn->close();

    header("Location: profile.php");
    exit();
} else {
    header("Location: profile.php");
    exit();
}

