<?php

session_start();
if (!isset($_SESSION['admin_logged']) || $_SESSION['admin_logged'] !== true) {
    header("Location: login.php");
    exit();
}


include 'config.php';

$conn = new mysqli($db_config['servername'], $db_config['username'], $db_config['password'], $db_config['dbname']);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT id, name, comment FROM comments WHERE approved = 0";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        echo "<div class='comment'>";
        echo "<p><strong>Name: </strong>" . $row["name"] . "</p>";
        echo "<p><strong>Comment: </strong>" . $row["comment"] . "</p>";
        echo "<form action='approve.php' method='POST'>";
        echo "<input type='hidden' name='id' value='" . $row["id"] . "'>";
        echo "<input type='submit' name='approve' value='Approve'>";
        echo "<input type='submit' name='reject' value='Reject'>";
        echo "</form>";
        echo "</div>";
    }
} else {
    echo "Nothing here.";
}

$conn->close();
?>


<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Dashboard</title>
</head>
<body>
</body>
</html>
