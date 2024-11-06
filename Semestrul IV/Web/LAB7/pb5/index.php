<?php

include 'config.php';

$conn = new mysqli($db_config['servername'], $db_config['username'], $db_config['password'], $db_config['dbname']);


if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $email = $_POST['email'];
    $password = $_POST["password"];

    $hashed_password = password_hash($password, PASSWORD_BCRYPT);

    $result = $conn->query("SELECT * FROM users WHERE email = '$email'");

    if ($result->num_rows == 1) {
        $row = $result->fetch_assoc();
        $stored_password = $row['password'];

        if (password_verify($password, $stored_password)) {
            session_start();
            $_SESSION['user_logged'] = true;
            $_SESSION['id_user'] = $row['id'];
            header("Location: dashboard.php");
            exit();
        } else {
            $error_message = "Date incorecte";
        }
    } else {
        $error_message = "Date incorecte";
    }
}
?>


<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
<?php
if (isset($error_message)) {
    echo "<p>$error_message</p>";
}
?>
<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
    <label for="email">Email:</label>
    <input type="text" id="email" name="email" required>
    <br>
    <label for="password">Password:</label>
    <input type="password" id="password" name="password" required>
    <br>
    <input type="submit" value="Login">
</form>
</body>
</html>
