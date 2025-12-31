<?php
$host = 'localhost';
$user = 'root';
$pass = 'ailab';
$db = '23mcce13';

$conn = new mysqli($host, $user, $pass, $db);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$search = isset($_POST['search']) ? $conn->real_escape_string($_POST['search']) : '';

$sql = "SELECT * FROM library WHERE name LIKE '%$search%'";
$result = $conn->query($sql);

$output = "";
if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $output .= "<tr>
                        <td>{$row['bookNumber']}</td>
                        <td>{$row['name']}</td>
                        <td>{$row['author']}</td>
                    </tr>";
    }
} else {
    $output = "<tr><td colspan='3'>No books found</td></tr>";
}
echo $output;

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>LIBRARY</title>
    <link rel="stylesheet" href="style.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <h1>LIBRARY</h1>
    <input id="search" type="text" placeholder="Enter book name">

    <table>
        <thead>
            <tr>
                <th>Book Id</th>
                <th>Book Name</th>
                <th>Author</th>
            </tr>
        </thead>
        <tbody id="bookTableBody">
            <!-- Rows will be added here dynamically -->
        </tbody>
    </table>

    <script>
        function fetchBooks(query = "") {
            $.ajax({
                url: "fetch_books.php",
                method: "POST",
                data: { search: query },
                success: function(response) {
                    $("#bookTableBody").html(response);
                }
            });
        }

        $(document).ready(function() {
            fetchBooks(); // Load all books initially

            $("#search").on("keyup", function() {
                let query = $(this).val();
                fetchBooks(query);
            });
        });
    </script>
</body>
</html>