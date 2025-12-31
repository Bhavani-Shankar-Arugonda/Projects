<?php
session_start();
include 'SSS_db_config.php';

if (!isset($_SESSION['user_id']) || $_SESSION['role'] != 'Supervisor') {
    header("Location: SSS_login_page.php");
    exit();
}

$message = "";


if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['add_normal_visitor'])) {
    //$building=$_POST['building_id'];
    $flat_id = $_POST['flat_id'];
    $visitor_name = $_POST['visitor_name'];
    $visitor_phone = $_POST['visitor_phone'];
    $purpose = $_POST['purpose'];
    
    $sql = "INSERT INTO visitor_details (flat_id, visitor_name, visitor_phone, purpose_of_visit, approval_status) 
            VALUES ($flat_id, '$visitor_name', '$visitor_phone', '$purpose', 'Pending')";
    
    if ($conn->query($sql)) {
        $message = "✓ Normal visitor registered successfully!";
    } else {
        $message = "Error: " . $conn->error;
    }
}

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['add_regular_visitor'])) {
    $visitor_name = $_POST['regular_visitor_name'];
    $visitor_phone = $_POST['regular_visitor_phone'];
    $visitor_email = $_POST['email'];
    $category = $_POST['category'];
    
    $sql = "INSERT INTO regular_visitors_vendors (name, phone_number,email, category, security_code, is_active) 
            VALUES ('$visitor_name', '$visitor_phone','$visitor_email', '$category', 'SEC-" . strtoupper(substr(md5(time() . rand()), 0, 6)) . "', 1)";
    
    if ($conn->query($sql)) {
        $message = "✓ Regular visitor/vendor added successfully!";
    } else {
        $message = "Error: " . $conn->error;
    }
}

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['add_maintenance'])) {
    $flat_id = $_POST['flat_id'];
    $maintenance_amount = $_POST['maintenance_amount'];
    $billing_month = $_POST['billing_month'];
    $due_date = $_POST['due_date'];
    $payment_mode = $_POST['payment_mode'];
    
    $sql = "INSERT INTO maintenance_details (flat_id, maintenance_amount, billing_month, due_date, payment_status, payment_mode) 
            VALUES ($flat_id, $maintenance_amount, '$billing_month', '$due_date', 'Pending', '$payment_mode')";
    
    if ($conn->query($sql)) {
        $message = "✓ Maintenance record added successfully!";
    } else {
        $message = "Error: " . $conn->error;
    }
}

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['approve_maintenance'])) {
    $maintenance_id = $_POST['maintenance_id'];
    $payment_status = $_POST['payment_status'];
    $payment_date = date('Y-m-d');
    
    $sql = "UPDATE maintenance_details SET payment_status = '$payment_status', payment_date = '$payment_date' 
            WHERE maintenance_id = $maintenance_id";
    
    if ($conn->query($sql)) {
        $message = "✓ Maintenance status updated successfully!";
    } else {
        $message = "Error: " . $conn->error;
    }
}

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['delete_regular_visitor'])) {
    $regular_visitor_id = $_POST['regular_visitor_id'];
    
    $sql = "DELETE FROM regular_visitors_vendors WHERE regular_visitor_id = $regular_visitor_id";
    
    if ($conn->query($sql)) {
        $message = "✓ Regular visitor deleted successfully!";
    } else {
        $message = "Error: " . $conn->error;
    }
}

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['add_staff'])) {
    $building_id = $_POST['building_id'];
    $staff_name = $_POST['staff_name'];
    $category = $_POST['category'];
    $phone = $_POST['phone'];
    $email = $_POST['email'];
    $salary = $_POST['salary'];
    $shift = $_POST['shift'];
    
    $sql = "INSERT INTO staff_details (building_id, staff_name, staff_category, phone_number, email, salary, shift_timing) 
            VALUES ($building_id, '$staff_name', '$category', '$phone', '$email', $salary, '$shift')";
    
    if ($conn->query($sql)) {
        $message = "✓ Staff member added successfully!";
    } else {
        $message = "Error: " . $conn->error;
    }
}

$buildings = $conn->query("SELECT * FROM building WHERE supervisor_id = " . $_SESSION['user_id']);

$selected_building_id = isset($_POST['building_id']) ? $_POST['building_id'] : null;

$flats = null;
if ($selected_building_id) {
    $flats = $conn->query("SELECT * FROM flat_details WHERE building_id = $selected_building_id");
}

$normal_visitors = $conn->query("SELECT v.*, f.flat_number, b.building_name FROM visitor_details v 
                          JOIN flat_details f ON v.flat_id = f.flat_id 
                          JOIN building b ON f.building_id = b.building_id 
                          ORDER BY v.visitor_id DESC");

if ($regular_visitors) {
    $regular_visitors->data_seek(0);
} else {
    $regular_visitors = $conn->query("SELECT * FROM regular_visitors_vendors ORDER BY regular_visitor_id DESC");
}

$staff_members = $conn->query("SELECT * FROM staff_details WHERE building_id IN 
                              (SELECT building_id FROM building WHERE supervisor_id = " . $_SESSION['user_id'] . ")");

$maintenance_records = $conn->query("SELECT m.*, f.flat_number, r.resident_name, b.building_name FROM maintenance_details m
                                    JOIN flat_details f ON m.flat_id = f.flat_id
                                    JOIN building b ON f.building_id = b.building_id
                                    LEFT JOIN resident_details r ON f.flat_id = r.flat_id
                                    WHERE b.supervisor_id = " . $_SESSION['user_id'] . "
                                    ORDER BY m.maintenance_id DESC");
?>

<!DOCTYPE html>
<html>
<head>
    <title>Supervisor Dashboard - SSS App</title>
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
            overflow-y: auto;
        }
        
        .sidebar h2 {
            margin-bottom: 30px;
            font-size: 18px;
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
            margin-bottom: 20px;
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
            color: #2c3e50;
        }
        
        tr:hover {
            background: #f9f9f9;
        }
        
        .form-row {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 15px;
        }
        
        h2 {
            color: #2c3e50;
            margin-bottom: 20px;
        }
        
        h3 {
            color: #34495e;
            margin-top: 30px;
            margin-bottom: 15px;
            font-size: 16px;
        }
        
        .badge {
            padding: 5px 10px;
            border-radius: 3px;
            font-size: 12px;
            font-weight: bold;
            color: white;
            display: inline-block;
        }
        
        .badge-pending {
            background: #f39c12;
        }
        
        .badge-approved {
            background: #27ae60;
        }
        
        .badge-rejected {
            background: #e74c3c;
        }
        
        .empty-msg {
            color: #7f8c8d;
            padding: 20px;
            text-align: center;
            font-style: italic;
        }
        
        a {
            color: white;
            text-decoration: none;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="sidebar">
            <h2> SSS Supervisor</h2>
            <div class="nav-item active" onclick="showSection('normal-visitor')">Add Normal Visitor</div>
            <div class="nav-item" onclick="showSection('regular-visitor')">Add Regular Visitor</div>
            <div class="nav-item" onclick="showSection('staff')">Add Staff</div>
            <div class="nav-item" onclick="showSection('maintenance')">Add Maintenance</div>
            <hr style="margin: 15px 0; opacity: 0.3;">
            <div class="nav-item" onclick="showSection('normal-visitors-list')">View Normal Visitors</div>
            <div class="nav-item" onclick="showSection('regular-visitors-list')">View Regular Visitors</div>
            <div class="nav-item" onclick="showSection('staff-list')">View Staff</div>
            <div class="nav-item" onclick="showSection('maintenance-list')">View Maintenance</div>
            <hr style="margin: 15px 0; opacity: 0.3;">
            <a href="SSS_logout.php">
                <div class="nav-item">Logout</div>
            </a>
        </div>
        
        <div class="main-content">
            <div class="top-bar">
                <h1>Supervisor Dashboard</h1>
                <span>Welcome, <?php echo $_SESSION['username']; ?></span>
            </div>
            
            <?php if ($message): ?>
                <div class="message"><?php echo $message; ?></div>
            <?php endif; ?>
            
            
            <div id="normal-visitor" class="section active">
                <h2>Register Normal Visitor</h2>
                <form method="POST">
                    <div class="form-row">
                        <div class="form-group">
                            <label>Building</label>
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
                        
                        <div class="form-group">
                            <label>Flat Number</label>
                            <select name="flat_id" required>
                                <option value="">Select Flat</option>
                                <?php 
                                if ($flats) {
                                    while($row = $flats->fetch_assoc()): 
                                ?>
                                    <option value="<?php echo $row['flat_id']; ?>">
                                        <?php echo $row['flat_number']; ?>
                                    </option>
                                <?php endwhile;
                                }
                                ?>
                            </select>
                        </div>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Visitor Name</label>
                            <input type="text" name="visitor_name" required>
                        </div>
                        <div class="form-group">
                            <label>Phone Number</label>
                            <input type="text" name="visitor_phone">
                        </div>
                    </div>
                    
                    <div class="form-group">
                        <label>Purpose of Visit</label>
                        <input type="text" name="purpose" required>
                    </div>
                    
                    <button type="submit" name="add_normal_visitor">Register Normal Visitor</button>
                </form>
            </div>
            
            
            <div id="regular-visitor" class="section">
                <h2>Add Regular Visitor / Vendor</h2>
                <form method="POST">
                    <div class="form-row">
                        <div class="form-group">
                            <label>Name</label>
                            <input type="text" name="regular_visitor_name" required>
                        </div>
                        <div class="form-group">
                            <label>Phone Number</label>
                            <input type="text" name="regular_visitor_phone" required>
                        </div>
                    </div>
                    <div class="form-group">
                                <label>Email</label>
                                <input type="text" name="email" required>
                    </div>
                    <div class="form-group">
                        <label>Category</label>
                        <select name="category" required>
                            <option value="">Select Category</option>
                            <option value="House_Help">House Help</option>
                            <option value="Plumber">Plumber</option>
                            <option value="Electrician">Electrician</option>
                            <option value="Gardener">Gardener</option>
                            <option value="Cook">Cook</option>
                            <option value="Maid">Maid</option>
                            <option value="Other">Other</option>
                        </select>
                    </div>
                    
                    <button type="submit" name="add_regular_visitor">Add Regular Visitor</button>
                </form>
            </div>
            
            
            <div id="staff" class="section">
                <h2>Add Staff Member</h2>
                <form method="POST">
                    <div class="form-group">
                        <label>Building</label>
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
                            <label>Staff Name</label>
                            <input type="text" name="staff_name" required>
                        </div>
                        <div class="form-group">
                            <label>Category</label>
                            <select name="category" required>
                                <option value="Security">Security</option>
                                <option value="Cleaning">Cleaning</option>
                                <option value="Gardener">Gardener</option>
                                <option value="Temple">Temple</option>
                                <option value="Clubhouse">Clubhouse</option>
                            </select>
                        </div>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Phone Number</label>
                            <input type="text" name="phone" required>
                        </div>
                        <div class="form-group">
                            <label>Email</label>
                            <input type="email" name="email">
                        </div>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Salary</label>
                            <input type="number" step="0.01" name="salary" required>
                        </div>
                        <div class="form-group">
                            <label>Shift Timing</label>
                            <input type="text" name="shift" placeholder="e.g., 9AM-5PM" required>
                        </div>
                    </div>
                    
                    <button type="submit" name="add_staff">Add Staff</button>
                </form>
            </div>
            
            
            <div id="normal-visitors-list" class="section">
                <h2>All Normal Visitors</h2>
                <?php if ($normal_visitors && $normal_visitors->num_rows > 0): ?>
                <table>
                    <tr>
                        <th>Visitor Name</th>
                        <th>Phone</th>
                        <th>Building</th>
                        <th>Flat</th>
                        <th>Purpose</th>
                        <th>Status</th>
                    </tr>
                    <?php 
                    while($row = $normal_visitors->fetch_assoc()): 
                    ?>
                    <tr>
                        <td><?php echo $row['visitor_name']; ?></td>
                        <td><?php echo $row['visitor_phone']; ?></td>
                        <td><?php echo $row['building_name']; ?></td>
                        <td><?php echo $row['flat_number']; ?></td>
                        <td><?php echo $row['purpose_of_visit']; ?></td>
                        <td><span class="badge badge-<?php echo strtolower($row['approval_status']); ?>"><?php echo $row['approval_status']; ?></span></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?>
                    <p class="empty-msg">No normal visitors found</p>
                <?php endif; ?>
            </div>
            
        
            <div id="regular-visitors-list" class="section">
                <h2>All Regular Visitors / Vendors</h2>
                <?php if ($regular_visitors && $regular_visitors->num_rows > 0): ?>
                <table>
                    <tr>
                        <th>Name</th>
                        <th>Category</th>
                        <th>Phone</th>
                        <th>Email</th>
                        <th>Security Code</th>
                        <th>Status</th>
                        <th>Action</th>
                    </tr>
                    <?php 
                    while($row = $regular_visitors->fetch_assoc()): 
                    ?>
                    <tr>
                        <td><?php echo $row['name']; ?></td>
                        <td><?php echo $row['category']; ?></td>
                        <td><?php echo $row['phone_number']; ?></td>
                        <td><?php echo $row['email']; ?></td>
                        <td><strong style="background: #ecf0f1; padding: 5px 10px; border-radius: 3px;"><?php echo $row['security_code']; ?></strong></td>
                        <td><?php echo $row['is_active'] ? 'Active' : 'Inactive'; ?></td>
                        <td>
                            <form method="POST" style="display:inline;" onsubmit="return confirm('Are you sure you want to delete this regular visitor?');">
                                <input type="hidden" name="regular_visitor_id" value="<?php echo $row['regular_visitor_id']; ?>">
                                <button type="submit" name="delete_regular_visitor" style="background: #e74c3c; padding: 5px 10px; font-size: 12px;">Delete</button>
                            </form>
                        </td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?>
                    <p class="empty-msg">No regular visitors found</p>
                <?php endif; ?>
            </div>
            
            
            <div id="staff-list" class="section">
                <h2>All Staff Members</h2>
                <?php if ($staff_members && $staff_members->num_rows > 0): ?>
                <table>
                    <tr>
                        <th>Name</th>
                        <th>Category</th>
                        <th>Phone</th>
                        <th>Email</th>
                        <th>Salary</th>
                        <th>Shift</th>
                    </tr>
                    <?php 
                    while($row = $staff_members->fetch_assoc()): 
                    ?>
                    <tr>
                        <td><?php echo $row['staff_name']; ?></td>
                        <td><?php echo $row['staff_category']; ?></td>
                        <td><?php echo $row['phone_number']; ?></td>
                        <td><?php echo $row['email']; ?></td>
                        <td><?php echo $row['salary']; ?></td>
                        <td><?php echo $row['shift_timing']; ?></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?>
                    <p class="empty-msg">No staff members found</p>
                <?php endif; ?>
            </div>
            
    
            <div id="maintenance" class="section">
                <h2>Add Maintenance Record</h2>
                <form method="POST">
                    <div class="form-row">
                        <div class="form-group">
                            <label>Select Building</label>
                            <select name="building_id" onchange="document.getElementById('flatSelect').innerHTML = this.value ? 'Loading...' : 'Select Flat';" required>
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
                        
                        <div class="form-group">
                            <label>Select Flat</label>
                            <select name="flat_id" id="flatSelect" required>
                                <option value="">Select Flat</option>
                                <?php 
                                if ($flats) {
                                    while($row = $flats->fetch_assoc()): 
                                ?>
                                    <option value="<?php echo $row['flat_id']; ?>">
                                        <?php echo $row['flat_number']; ?>
                                    </option>
                                <?php endwhile;
                                }
                                ?>
                            </select>
                        </div>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Maintenance Amount</label>
                            <input type="number" step="0.01" name="maintenance_amount" required>
                        </div>
                        <div class="form-group">
                            <label>Billing Month</label>
                            <input type="date" name="billing_month" required>
                        </div>
                    </div>
                    
                    <div class="form-row">
                        <div class="form-group">
                            <label>Due Date</label>
                            <input type="date" name="due_date" required>
                        </div>
                        <div class="form-group">
                            <label>Payment Mode</label>
                            <select name="payment_mode" required>
                                <option value="Online">Online</option>
                                <option value="Cash">Cash</option>
                                <option value="Cheque">Cheque</option>
                                <option value="Bank_Transfer">Bank Transfer</option>
                            </select>
                        </div>
                    </div>
                    
                    <button type="submit" name="add_maintenance">Add Maintenance Record</button>
                </form>
            </div>
            
            
            <div id="maintenance-list" class="section">
                <h2>All Maintenance Records</h2>
                <?php if ($maintenance_records && $maintenance_records->num_rows > 0): ?>
                <table>
                    <tr>
                        <th>Building</th>
                        <th>Flat</th>
                        <th>Resident</th>
                        <th>Amount</th>
                        <th>Billing Month</th>
                        <th>Due Date</th>
                        <th>Status</th>
                        <th>Action</th>
                    </tr>
                    <?php 
                    while($row = $maintenance_records->fetch_assoc()): 
                    ?>
                    <tr>
                        <td><?php echo $row['building_name']; ?></td>
                        <td><?php echo $row['flat_number']; ?></td>
                        <td><?php echo $row['resident_name'] ?: 'N/A'; ?></td>
                        <td>₹<?php echo $row['maintenance_amount']; ?></td>
                        <td><?php echo $row['billing_month']; ?></td>
                        <td><?php echo $row['due_date']; ?></td>
                        <td><span class="badge badge-<?php echo strtolower(str_replace(' ', '_', $row['payment_status'])); ?>"><?php echo $row['payment_status']; ?></span></td>
                        <td>
                            <?php if ($row['payment_status'] == 'Pending'): ?>
                            <form method="POST" style="display:inline;">
                                <input type="hidden" name="maintenance_id" value="<?php echo $row['maintenance_id']; ?>">
                                <input type="hidden" name="payment_status" value="Paid">
                                <button type="submit" name="approve_maintenance" style="background: #27ae60; padding: 5px 10px; font-size: 12px;">Mark Paid</button>
                            </form>
                            <?php endif; ?>
                        </td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?>
                    <p class="empty-msg">No maintenance records found</p>
                <?php endif; ?>
            </div>
        </div>
    </div>
    
    <script>
        function showSection(sectionId) {
            const sections = document.querySelectorAll('.section');
            sections.forEach(section => section.classList.remove('active'));
            
            const navItems = document.querySelectorAll('.nav-item');
            navItems.forEach(item => item.classList.remove('active'));
            
            document.getElementById(sectionId).classList.add('active');
            event.target.classList.add('active');
        }
    </script>
</body>
</html>