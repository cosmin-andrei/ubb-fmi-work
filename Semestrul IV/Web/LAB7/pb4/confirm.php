<?php
include 'config.php';
$conn = new mysqli($db_config['servername'], $db_config['username'], $db_config['password'], $db_config['dbname']);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if (isset($_GET['email'])) {
    $email = $_GET['email'];

    $stmt = $conn->prepare("SELECT * FROM users WHERE email = ? AND is_active = 0");
    $stmt->bind_param("s", $email);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows > 0) {
        $stmt = $conn->prepare("UPDATE users SET is_active = 1 WHERE email = ?");
        $stmt->bind_param("s", $email);
        if ($stmt->execute()) {
            echo "OK. Account active!";
        } else {
            echo "Error: " . $stmt->error;
        }
    } else {
        echo "Account already active.";
    }
    $stmt->close();
} else {
    echo "Link invalid.";
}

$conn->close();

