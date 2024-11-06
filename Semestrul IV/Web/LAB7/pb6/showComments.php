<?php

include 'config.php';

$conn = new mysqli($db_config['servername'], $db_config['username'], $db_config['password'], $db_config['dbname']);



if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$result = $conn->query("SELECT name, comment FROM comments WHERE approved = 1");

if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        echo "<div class='comment'>";
        echo "<p><strong>Name: </strong>" . $row["name"] . "</p>";
        echo "<p><strong>Comment: </strong>" . $row["comment"] . "</p>";
        echo "</div>";
    }
} else {
    echo "No comments yet";
}
