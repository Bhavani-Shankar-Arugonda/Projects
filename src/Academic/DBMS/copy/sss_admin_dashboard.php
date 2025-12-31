<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

session_start();
include 'SSS_db_config.php';

// Check if user is logged in and is Admin
if (!isset($_SESSION['user_id']) || $_SESSION['role'] != 'Admin') {
    header("Location: SSS_login_page.php");
    exit();
}

$message = "";
$debug = "";

// Add Supervisor
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['add_supervisor'])) {
    $username = $_POST['sup_username'];
    $password = $_POST['sup_password'];
    $sup_name = $_POST['sup_name'];
    $sup_phone = $_POST['sup_phone'];
    $sup_email = $_POST['sup_email'];
    $building_ids = isset($_POST['building_ids']) ? $_POST['building_ids'] : array();
    
    $sql = "INSERT INTO users (username, password, role, is_active) 
            VALUES ('$username', '$password', 'Supervisor', 1)";
    
    if ($conn->query($sql)) {
        $supervisor_id = $conn->insert_id;
        
        // Assign selected buildings to supervisor
        $assigned = 0;
        foreach ($building_ids as $building_id) {
            $update_sql = "UPDATE building SET supervisor_id = $supervisor_id WHERE building_id = $building_id";
            if ($conn->query($update_sql)) {
                $assigned++;
            }
        }
        
        $message = "✓ Supervisor added successfully! Assigned to " . $assigned . " building(s).";
    } else {
        $message = "Error: " . $conn->error;
    }
}

// Add Resident
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['add_resident'])) {
    $flat_id = $_POST['flat_id'];
    $username = $_POST['res_username'];
    $password = $_POST['res_password'];
    $resident_name = $_POST['resident_name'];
    $age = $_POST['age'];
    $gender = $_POST['gender'];
    $phone = $_POST['phone'];
    $email = $_POST['email'];
    
    // Insert user first
    $sql1 = "INSERT INTO users (username, password, role, is_active) 
             VALUES ('$username', '$password', 'Resident', 1)";
    
    if ($conn->query($sql1)) {
        $user_id = $conn->insert_id;
        
        // Insert resident details
        $sql2 = "INSERT INTO resident_details (flat_id, user_id, resident_name, age, gender, phone_number, email) 
                 VALUES ($flat_id, $user_id, '$resident_name', $age, '$gender', '$phone', '$email')";
        
        if ($conn->query($sql2)) {
            $message = "✓ Resident added successfully!";
        } else {
            $message = "Error: " . $conn->error;
        }
    } else {
        $message = "Error: " . $conn->error;
    }
}

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
        $message = "✓ Building added successfully!";
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
        $message = "✓ Flat added successfully!";
    } else {
        $message = "Error: " . $conn->error;
    }
}

// Fetch data
$supervisors = $conn->query("SELECT * FROM users WHERE role = 'Supervisor'");
$buildings = $conn->query("SELECT * FROM building");
$flats = $conn->query("SELECT f.*, b.building_name FROM flat_details f JOIN building b ON f.building_id = b.building_id ORDER BY f.flat_id DESC");
$residents = $conn->query("SELECT r.*, f.flat_number, b.building_name, u.username FROM resident_details r 
                          JOIN flat_details f ON r.flat_id = f.flat_id 
                          JOIN building b ON f.building_id = b.building_id
                          JOIN users u ON r.user_id = u.user_id
                          ORDER BY r.resident_id DESC");
?>

<!DOCTYPE html>
<html>
<head>
    <title>Admin Dashboard - SSS App</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { font-family: Arial, sans-serif; background: #f5f5f5; }
        .container { display: flex; height: 100vh; }
        .sidebar { width: 250px; background: #2c3e50; color: white; padding: 20px; overflow-y: auto; }
        .sidebar h2 { margin-bottom: 30px; font-size: 18px; }
        .nav-item { padding: 12px; margin-bottom: 10px; background: #34495e; cursor: pointer; border-radius: 5px; transition: 0.3s; }
        .nav-item:hover { background: #1a252f; }
        .nav-item.active { background: #667eea; }
        .main-content { flex: 1; padding: 30px; overflow-y: auto; }
        .top-bar { display: flex; justify-content: space-between; align-items: center; background: white; padding: 15px 20px; border-radius: 5px; margin-bottom: 30px; box-shadow: 0 2px 5px rgba(0,0,0,0.1); }
        .section { background: white; padding: 20px; margin-bottom: 20px; border-radius: 5px; box-shadow: 0 2px 5px rgba(0,0,0,0.1); display: none; }
        .section.active { display: block; }
        .form-group { margin-bottom: 15px; }
        label { display: block; margin-bottom: 5px; font-weight: bold; }
        input, select { width: 100%; padding: 10px; border: 1px solid #ddd; border-radius: 5px; font-size: 14px; }
        button { background: #667eea; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; font-weight: bold; margin-bottom: 20px; }
        button:hover { background: #764ba2; }
        .message { padding: 15px; background: #d4edda; color: #155724; border: 1px solid #c3e6cb; border-radius: 5px; margin-bottom: 20px; }
        table { width: 100%; border-collapse: collapse; margin-top: 20px; }
        th, td { padding: 12px; text-align: left; border-bottom: 1px solid #ddd; }
        th { background: #f9f9f9; font-weight: bold; color: #2c3e50; }
        tr:hover { background: #f9f9f9; }
        .form-row { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; }
        h2 { color: #2c3e50; margin-bottom: 20px; }
        .empty-msg { color: #7f8c8d; padding: 20px; text-align: center; }
        a { color: white; text-decoration: none; }
    </style>
</head>
<body>
    <div class="container">
        <div class="sidebar">
            <h2>🏢 SSS Admin</h2>
            <div class="nav-item active" onclick="showSection('add-supervisor')">Add Supervisor</div>
            <div class="nav-item" onclick="showSection('add-resident')">Add Resident</div>
            <div class="nav-item" onclick="showSection('add-building')">Add Building</div>
            <div class="nav-item" onclick="showSection('add-flat')">Add Flat</div>
            <hr style="margin: 15px 0; opacity: 0.3;">
            <div class="nav-item" onclick="showSection('view-supervisors')">View Supervisors</div>
            <div class="nav-item" onclick="showSection('view-buildings')">View Buildings</div>
            <div class="nav-item" onclick="showSection('view-flats')">View Flats</div>
            <div class="nav-item" onclick="showSection('view-residents')">View Residents</div>
            <hr style="margin: 15px 0; opacity: 0.3;">
            <a href="SSS_logout.php">
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
            
            <!-- Add Supervisor Section -->
            <div id="add-supervisor" class="section active">
                <h2>Add New Supervisor</h2>
                <form method="POST">
                    <div class="form-row">
                        <div class="form-group">
                            <label>Username</label>
                            <input type="text" name="sup_username" required>
                        </div>
                        <div class="form-group">
                            <label>Password</label>
                            <input type="password" name="sup_password" required>
                        </div>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Supervisor Name</label>
                            <input type="text" name="sup_name" required>
                        </div>
                        <div class="form-group">
                            <label>Phone</label>
                            <input type="text" name="sup_phone">
                        </div>
                    </div>
                    
                    <div class="form-group">
                        <label>Email</label>
                        <input type="email" name="sup_email">
                    </div>
                    
                    <div class="form-group">
                        <label>Assign Buildings (Select one or more)</label>
                        <div style="border: 1px solid #ddd; padding: 10px; border-radius: 5px; max-height: 200px; overflow-y: auto;">
                            <?php 
                            $buildings->data_seek(0);
                            $has_buildings = false;
                            while($row = $buildings->fetch_assoc()): 
                                $has_buildings = true;
                            ?>
                                <div style="margin-bottom: 8px;">
                                    <label style="display: flex; align-items: center; font-weight: normal; margin-bottom: 0;">
                                        <input type="checkbox" name="building_ids[]" value="<?php echo $row['building_id']; ?>" style="margin-right: 8px;">
                                        <?php echo $row['building_name'] . " (" . $row['city'] . ")"; ?>
                                    </label>
                                </div>
                            <?php endwhile; 
                            if (!$has_buildings):
                            ?>
                                <p style="color: #999;">No buildings available. Please create buildings first.</p>
                            <?php endif; ?>
                        </div>
                    </div>
                    
                    <button type="submit" name="add_supervisor">Add Supervisor</button>
                </form>
            </div>
            
            <!-- Add Resident Section -->
            <div id="add-resident" class="section">
                <h2>Add New Resident</h2>
                <form method="POST">
                    <div class="form-group">
                        <label>Select Flat</label>
                        <select name="flat_id" required>
                            <option value="">Select Flat</option>
                            <?php 
                            $flats->data_seek(0);
                            while($row = $flats->fetch_assoc()): 
                            ?>
                                <option value="<?php echo $row['flat_id']; ?>">
                                    <?php echo $row['building_name'] . " - Flat " . $row['flat_number']; ?>
                                </option>
                            <?php endwhile; ?>
                        </select>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Username</label>
                            <input type="text" name="res_username" required>
                        </div>
                        <div class="form-group">
                            <label>Password</label>
                            <input type="password" name="res_password" required>
                        </div>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Resident Name</label>
                            <input type="text" name="resident_name" required>
                        </div>
                        <div class="form-group">
                            <label>Age</label>
                            <input type="number" name="age">
                        </div>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Gender</label>
                            <select name="gender">
                                <option value="Male">Male</option>
                                <option value="Female">Female</option>
                                <option value="Other">Other</option>
                            </select>
                        </div>
                        <div class="form-group">
                            <label>Phone</label>
                            <input type="text" name="phone" required>
                        </div>
                    </div>
                    
                    <div class="form-group">
                        <label>Email</label>
                        <input type="email" name="email">
                    </div>
                    
                    <button type="submit" name="add_resident">Add Resident</button>
                </form>
            </div>
            
            <!-- Add Building Section -->
            <div id="add-building" class="section">
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
                        <label>Address</label>
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
                                <?php 
                                $supervisors->data_seek(0);
                                while($row = $supervisors->fetch_assoc()): 
                                ?>
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
            <div id="add-flat" class="section">
                <h2>Add New Flat</h2>
                <form method="POST">
                    <div class="form-group">
                        <label>Select Building</label>
                        <select name="building_id" required>
                            <option value="">Select Building</option>
                            <?php 
                            $buildings->data_seek(0);
                            while($row = $buildings->fetch_assoc()): 
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
            
            <!-- View Supervisors Section -->
            <div id="view-supervisors" class="section">
                <h2>All Supervisors</h2>
                <?php if ($supervisors && $supervisors->num_rows > 0): ?>
                <table>
                    <tr>
                        <th>Username</th>
                        <th>Email</th>
                        <th>Status</th>
                        <th>Action</th>
                    </tr>
                    <?php 
                    $supervisors->data_seek(0);
                    while($row = $supervisors->fetch_assoc()): 
                    ?>
                    <tr>
                        <td><?php echo $row['username']; ?></td>
                        <td><?php echo $row['email'] ?: 'N/A'; ?></td>
                        <td><?php echo $row['is_active'] ? 'Active' : 'Inactive'; ?></td>
                        <td>
                            <form method="POST" style="display:inline;" onsubmit="return confirm('Are you sure? This will unassign all their buildings.');">
                                <input type="hidden" name="user_id" value="<?php echo $row['user_id']; ?>">
                                <button type="submit" name="delete_supervisor" style="background: #e74c3c; padding: 5px 10px; font-size: 12px; border: none; border-radius: 3px; color: white; cursor: pointer;">Delete</button>
                            </form>
                        </td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?>
                    <p class="empty-msg">No supervisors found</p>
                <?php endif; ?>
            </div>
            
            <!-- View Buildings Section -->
            <div id="view-buildings" class="section">
                <h2>All Buildings</h2>
                <?php if ($buildings && $buildings->num_rows > 0): ?>
                <table>
                    <tr>
                        <th>Building Name</th>
                        <th>Address</th>
                        <th>City</th>
                        <th>Postal Code</th>
                        <th>Floors</th>
                        <th>Flats</th>
                    </tr>
                    <?php 
                    $buildings->data_seek(0);
                    while($row = $buildings->fetch_assoc()): 
                    ?>
                    <tr>
                        <td><?php echo $row['building_name']; ?></td>
                        <td><?php echo $row['building_address']; ?></td>
                        <td><?php echo $row['city']; ?></td>
                        <td><?php echo $row['postal_code']; ?></td>
                        <td><?php echo $row['total_floors']; ?></td>
                        <td><?php echo $row['total_flats']; ?></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?>
                    <p class="empty-msg">No buildings found</p>
                <?php endif; ?>
            </div>
            
            <!-- View Flats Section -->
            <div id="view-flats" class="section">
                <h2>All Flats</h2>
                <?php if ($flats && $flats->num_rows > 0): ?>
                <table>
                    <tr>
                        <th>Building</th>
                        <th>Flat Number</th>
                        <th>Floor</th>
                        <th>Type</th>
                    </tr>
                    <?php 
                    $flats->data_seek(0);
                    while($row = $flats->fetch_assoc()): 
                    ?>
                    <tr>
                        <td><?php echo $row['building_name']; ?></td>
                        <td><?php echo $row['flat_number']; ?></td>
                        <td><?php echo $row['floor_number']; ?></td>
                        <td><?php echo $row['flat_type']; ?></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?>
                    <p class="empty-msg">No flats found</p>
                <?php endif; ?>
            </div>
            
            <!-- View Residents Section -->
            <div id="view-residents" class="section">
                <h2>All Residents</h2>
                <?php if ($residents && $residents->num_rows > 0): ?>
                <table>
                    <tr>
                        <th>Name</th>
                        <th>Username</th>
                        <th>Building</th>
                        <th>Flat</th>
                        <th>Phone</th>
                        <th>Email</th>
                        <th>Action</th>
                    </tr>
                    <?php 
                    $residents->data_seek(0);
                    while($row = $residents->fetch_assoc()): 
                    ?>
                    <tr>
                        <td><?php echo $row['resident_name']; ?></td>
                        <td><?php echo $row['username']; ?></td>
                        <td><?php echo $row['building_name']; ?></td>
                        <td><?php echo $row['flat_number']; ?></td>
                        <td><?php echo $row['phone_number']; ?></td>
                        <td><?php echo $row['email']; ?></td>
                        <td>
                            <form method="POST" style="display:inline;" onsubmit="return confirm('Are you sure? This will permanently delete this resident.');">
                                <input type="hidden" name="resident_id" value="<?php echo $row['resident_id']; ?>">
                                <input type="hidden" name="user_id" value="<?php echo $row['user_id']; ?>">
                                <button type="submit" name="delete_resident" style="background: #e74c3c; padding: 5px 10px; font-size: 12px; border: none; border-radius: 3px; color: white; cursor: pointer;">Delete</button>
                            </form>
                        </td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?>
                    <p class="empty-msg">No residents found</p>
                <?php endif; ?>
            </div>
        </div>
    </div>
    
    <script>
        function showSection(id) {
            document.querySelectorAll('.section').forEach(s => s.classList.remove('active'));
            document.querySelectorAll('.nav-item').forEach(n => n.classList.remove('active'));
            document.getElementById(id).classList.add('active');
            event.target.classList.add('active');
        }
    </script>
</body>
</html>