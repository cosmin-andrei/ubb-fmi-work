<?php
$conn = mysqli_connect("localhost", "root", "", "lab6");
if (!$conn) {
    die('Could not connect: ' . mysqli_error($conn));
}

$result = mysqli_query($conn, "SELECT id FROM persons2");
echo '<option value="" disabled selected>Select a person</option>';
while ($row = mysqli_fetch_array($result)) {
    echo '<option value="' . $row[0] . '">' . $row[0] . '</option>';
}
mysqli_close($conn);

