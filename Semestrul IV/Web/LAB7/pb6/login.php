<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST['username'];
    $password = $_POST['password'];

    $correct_username = "cosmin";
    $correct_password = "2003";

    if ($username === $correct_username && $password === $correct_password) {
        session_start();
        $_SESSION['admin_logged'] = true;
        header("Location: dashboard.php");
        exit();
    } else {
        $error_message = "Date login gresite";
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
    <label for="username">Username:</label>
    <input type="text" id="username" name="username" required>
    <br>
    <label for="password">Password:</label>
    <input type="password" id="password" name="password" required>
    <br>
    <input type="submit" value="Login">
</form>
</body>
</html>
