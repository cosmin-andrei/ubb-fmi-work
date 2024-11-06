<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>pb6</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
<div class="container">
    <h2>Comments</h2>
    <div class="comment">
        <?php include 'showComments.php'; ?>
    </div>

    <h2>Add comment</h2>
    <form action="addComm.php" method="POST">
        <label for="name">Name</label>
        <input type="text" id="name" name="name" required>
        <br>
        <label for="comment">Comment</label>
        <textarea id="comment" name="comment" rows="3" required></textarea>
        <br>
        <input type="submit" value="Send">
    </form>
</div>
</body>
</html>
