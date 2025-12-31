<?php
session_start();
include 'SSS_db_config.php';

// Check if user is logged in and is Admin
if (!isset($_SESSION['user_id']) || $_SESSION['role'] != 'Admin') {
    header("Location: SSS_login_page.php");
    exit();
}

$message = "";

// Add Building
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['add_building'])) {
    $building_name = $_POST['building_name'];
    $building_address = $_POST['building_address'];
    $city = $_POST['city'];
    $postal_code = $_POST['postal_code'];
    $total_floors = $_POST['total_floors'];
    $total_flats = $_POST['total_flats'];
    $supervisor_id = $_POST['supervisor_id'];
    
    $sql = "INSERT INTO building (building_name, building_address, city, postal_code, total_floors, total_flats, supervisor_id) 
            VALUES ('$building_name', '$building_address', '$city', '$postal_code', $total_floors, $total_flats, $supervisor_id)";
    
    if ($conn->query($sql)) {
        $message = "Building added successfully!";
    } else {
        $message = "Error: " . $conn->error;
    }
}

// Add Flat
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['add_flat'])) {
    $building_id = $_POST['building_id'];
    $flat_number = $_POST['flat_number'];
    $floor_number = $_POST['floor_number'];
    $flat_type = $_POST['flat_type'];
    
    $sql = "INSERT INTO flat_details (building_id, flat_number, floor_number, flat_type) 
            VALUES ($building_id, '$flat_number', $floor_number, '$flat_type')";
    
    if ($conn->query($sql)) {
        $message = "Flat added successfully!";
    } else {
        $message = "Error: " . $conn->error;
    }
}

// Fetch all buildings
$buildings_result = $conn->query("SELECT * FROM building");

// Fetch supervisors
$supervisors = $conn->query("SELECT * FROM users WHERE role = 'Supervisor'");
?>

<!DOCTYPE html>
<html>
<head>
    <title>Admin Dashboard - SSS App</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: Arial, sans-serif;
            background: #f5f5f5;
        }
        
        .container {
            display: flex;
            height: 100vh;
        }
        
        .sidebar {
            width: 250px;
            background: #2c3e50;
            color: white;
            padding: 20px;
        }
        
        .sidebar h2 {
            margin-bottom: 30px;
        }
        
        .nav-item {
            padding: 12px;
            margin-bottom: 10px;
            background: #34495e;
            cursor: pointer;
            border-radius: 5px;
            transition: background 0.3s;
        }
        
        .nav-item:hover {
            background: #1a252f;
        }
        
        .nav-item.active {
            background: #667eea;
        }
        
        .main-content {
            flex: 1;
            overflow-y: auto;
            padding: 30px;
        }
        
        .top-bar {
            display: flex;
            justify-content: space-between;
            align-items: center;
            background: white;
            padding: 15px 20px;
            border-radius: 5px;
            margin-bottom: 30px;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
        }
        
        .logout-btn {
            background: #e74c3c;
            color: white;
            padding: 8px 15px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        
        .section {
            background: white;
            padding: 20px;
            margin-bottom: 20px;
            border-radius: 5px;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
            display: none;
        }
        
        .section.active {
            display: block;
        }
        
        .form-group {
            margin-bottom: 15px;
        }
        
        label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
            color: #333;
        }
        
        input, select {
            width: 100%;
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 5px;
            font-size: 14px;
        }
        
        button {
            background: #667eea;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-weight: bold;
        }
        
        button:hover {
            background: #764ba2;
        }
        
        .message {
            padding: 15px;
            background: #d4edda;
            color: #155724;
            border: 1px solid #c3e6cb;
            border-radius: 5px;
            margin-bottom: 20px;
        }
        
        .form-row {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 15px;
        }
        
        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }
        
        th, td {
            padding: 12px;
            text-align: left;
            border-bottom: 1px solid #ddd;
        }
        
        th {
            background: #f9f9f9;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="sidebar">
            <h2>🏢 SSS Admin</h2>
            <div class="nav-item active" onclick="showSection('buildings')">Manage Buildings</div>
            <div class="nav-item" onclick="showSection('flats')">Manage Flats</div>
            <div class="nav-item" onclick="showSection('buildings-list')">View Buildings</div>
            <hr style="margin: 20px 0; opacity: 0.3;">
            <a href="SSS_logout.php" style="color: white; text-decoration: none;">
                <div class="nav-item">Logout</div>
            </a>
        </div>
        
        <div class="main-content">
            <div class="top-bar">
                <h1>Admin Dashboard</h1>
                <span>Welcome, <?php echo $_SESSION['username']; ?></span>
            </div>
            
            <?php if ($message): ?>
                <div class="message"><?php echo $message; ?></div>
            <?php endif; ?>
            
            <!-- Add Building Section -->
            <div id="buildings" class="section active">
                <h2>Add New Building</h2>
                <form method="POST">
                    <div class="form-row">
                        <div class="form-group">
                            <label>Building Name</label>
                            <input type="text" name="building_name" required>
                        </div>
                        <div class="form-group">
                            <label>City</label>
                            <input type="text" name="city" required>
                        </div>
                    </div>
                    
                    <div class="form-group">
                        <label>Building Address</label>
                        <input type="text" name="building_address" required>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Postal Code</label>
                            <input type="text" name="postal_code" required>
                        </div>
                        <div class="form-group">
                            <label>Total Floors</label>
                            <input type="number" name="total_floors" required>
                        </div>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Total Flats</label>
                            <input type="number" name="total_flats" required>
                        </div>
                        <div class="form-group">
                            <label>Assign Supervisor</label>
                            <select name="supervisor_id" required>
                                <option value="">Select Supervisor</option>
                                <?php while($row = $supervisors->fetch_assoc()): ?>
                                    <option value="<?php echo $row['user_id']; ?>">
                                        <?php echo $row['username']; ?>
                                    </option>
                                <?php endwhile; ?>
                            </select>
                        </div>
                    </div>
                    
                    <button type="submit" name="add_building">Add Building</button>
                </form>
            </div>
            
            <!-- Add Flat Section -->
            <div id="flats" class="section">
                <h2>Add New Flat</h2>
                <form method="POST">
                    <div class="form-group">
                        <label>Select Building</label>
                        <select name="building_id" required>
                            <option value="">Select Building</option>
                            <?php 
                            $buildings_result->data_seek(0);
                            while($row = $buildings_result->fetch_assoc()): 
                            ?>
                                <option value="<?php echo $row['building_id']; ?>">
                                    <?php echo $row['building_name']; ?>
                                </option>
                            <?php endwhile; ?>
                        </select>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Flat Number</label>
                            <input type="text" name="flat_number" required>
                        </div>
                        <div class="form-group">
                            <label>Floor Number</label>
                            <input type="number" name="floor_number" required>
                        </div>
                    </div>
                    
                    <div class="form-group">
                        <label>Flat Type</label>
                        <select name="flat_type" required>
                            <option value="1BHK">1BHK</option>
                            <option value="2BHK">2BHK</option>
                            <option value="3BHK">3BHK</option>
                            <option value="4BHK">4BHK</option>
                        </select>
                    </div>
                    
                    <button type="submit" name="add_flat">Add Flat</button>
                </form>
            </div>
            
            <!-- View Buildings Section -->
            <div id="buildings-list" class="section">
                <h2>All Buildings</h2>
                <table>
                    <tr>
                        <th>Building Name</th>
                        <th>Address</th>
                        <th>City</th>
                        <th>Floors</th>
                        <th>Flats</th>
                    </tr>
                    <?php 
                    $buildings_result->data_seek(0);
                    while($row = $buildings_result->fetch_assoc()): 
                    ?>
                    <tr>
                        <td><?php echo $row['building_name']; ?></td>
                        <td><?php echo $row['building_address']; ?></td>
                        <td><?php echo $row['city']; ?></td>
                        <td><?php echo $row['total_floors']; ?></td>
                        <td><?php echo $row['total_flats']; ?></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
            </div>
        </div>
    </div>
    
    <script>
        function showSection(sectionId) {
            // Hide all sections
            const sections = document.querySelectorAll('.section');
            sections.forEach(section => section.classList.remove('active'));
            
            // Remove active class from all nav items
            const navItems = document.querySelectorAll('.nav-item');
            navItems.forEach(item => item.classList.remove('active'));
            
            // Show selected section
            document.getElementById(sectionId).classList.add('active');
            event.target.classList.add('active');
        }
    </script>
</body>
</html>
