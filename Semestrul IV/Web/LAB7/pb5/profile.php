<?php
session_start();
if (!isset($_SESSION['user_logged']) || $_SESSION['user_logged'] !== true) {
    header("Location: login.php");
    exit();
}
?>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Profile</title>
</head>
<body>

<?php

include 'config.php';
$conn = new mysqli($db_config['servername'], $db_config['username'], $db_config['password'], $db_config['dbname']);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$id = $_SESSION['id_user'];
$sql = "SELECT * FROM images WHERE id_user = $id";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        echo "<img src='uploads/{$row['image_name']}' alt='image' style='max-width: 500px; max-height: 500px;'>";
        echo "<a href='delete.php?image_id={$row['id']}'>Delete</a>";
        echo "<br>";
    }
} else {
    echo "No image.";
}
$conn->close();
?>
</body>
</html>

