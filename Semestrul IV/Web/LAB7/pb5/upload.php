<?php
include 'config.php';

$conn = new mysqli($db_config['servername'], $db_config['username'], $db_config['password'], $db_config['dbname']);


if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}


session_start();

if (!isset($_SESSION['user_logged']) || $_SESSION['user_logged'] !== true) {
    header("Location: login.php");
    exit();
}

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_FILES["image"])) {
    $id = $_SESSION['id_user'];
    $target_dir = "uploads/";
    $target_file = $target_dir . basename($_FILES["image"]["name"]);
    $uploadOk = 1;
    $imageFileType = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));

    $check = getimagesize($_FILES["image"]["tmp_name"]);
    if ($check !== false) {
        $uploadOk = 1;
    } else {
        $error_message = "Not an image.";
        $uploadOk = 0;
    }

    if (file_exists($target_file)) {
        $error_message = "Image exist.";
        $uploadOk = 0;
    }
    if ($_FILES["image"]["size"] > 5000000) {
        $error_message = "High size";
        $uploadOk = 0;
    }
    if ($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
        && $imageFileType != "gif") {
        $error_message = "Not our type.";
        $uploadOk = 0;
    }

    if ($uploadOk == 1) {
        if (move_uploaded_file($_FILES["image"]["tmp_name"], $target_file)) {
            $image_name = basename($_FILES["image"]["name"]);
            $conn->query("INSERT INTO images (id_user, image_name) VALUES ('$id', '$image_name')");
            $success_message = "Succes.";
        } else {
            $error_message = "Error";
        }
    }
}
?>
<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Upload</title>
</head>
<body>
<?php if (isset($error_message)) echo "<p>$error_message</p>"; ?>
<?php if (isset($success_message)) echo "<p>$success_message</p>"; ?>
<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post" enctype="multipart/form-data">
    Select img
    <input type="file" name="image" id="image">
    <input type="submit" value="Upload" name="submit">
</form>
</body>
</html>
