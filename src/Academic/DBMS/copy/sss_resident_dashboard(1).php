<?php
session_start();
include 'SSS_db_config.php';

// Check if user is logged in and is Resident
if (!isset($_SESSION['user_id']) || $_SESSION['role'] != 'Resident') {
    header("Location: SSS_login_page.php");
    exit();
}

$message = "";

// Get resident information
$resident_query = "SELECT * FROM resident_details WHERE user_id = " . $_SESSION['user_id'];
$resident_result = $conn->query($resident_query);
$resident = $resident_result->fetch_assoc();
// if (!$resident) {
//     // If no resident record is found for this user, stop the script.
//     die("Error: No resident details found for this user account. Please contact admin.");
// }
$flat_id = $resident['flat_id'];

// Approve/Reject Visitor
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['approve_visitor'])) {
    $visitor_id = $_POST['visitor_id'];
    $action = $_POST['action'];
    
    $status = ($action == 'approve') ? 'Approved' : 'Rejected';
    $sql = "UPDATE visitor_details SET approval_status = '$status', approved_by = " . $resident['resident_id'] . " 
            WHERE visitor_id = $visitor_id";
    
    if ($conn->query($sql)) {
        $message = "Visitor request updated successfully!";
    }
}

// Add Regular Visitor
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['add_regular_visitor'])) {
    $visitor_name = $_POST['visitor_name'];
    $visitor_phone = $_POST['visitor_phone'];
    $category = $_POST['category'];
    
    // Generate security code
    $security_code = strtoupper(substr(md5(time() . rand()), 0, 8));
    
    $sql = "INSERT INTO regular_visitors_vendors (name, phone_number, category, security_code, is_active) 
            VALUES ('$visitor_name', '$visitor_phone', '$category', '$security_code', 1)";
    
    if ($conn->query($sql)) {
        $message = "Regular visitor added! Security Code: " . $security_code;
    } else {
        $message = "Error: " . $conn->error;
    }
}

// Fetch pending visitors for this flat
$pending_visitors = $conn->query(
    "SELECT * FROM visitor_details WHERE flat_id = $flat_id AND approval_status = 'Pending'"
);

// Fetch all visitors for this flat
$all_visitors = $conn->query(
    "SELECT * FROM visitor_details WHERE flat_id = $flat_id ORDER BY visitor_id DESC"
);

// Fetch regular visitors
$regular_visitors = $conn->query("SELECT * FROM regular_visitors_vendors WHERE is_active = 1");

// Fetch maintenance details
$maintenance = $conn->query("SELECT * FROM maintenance_details WHERE flat_id = $flat_id ORDER BY billing_month DESC");

// Fetch check-in/check-out records
$checkins = $conn->query(
    "SELECT c.*, r.name, r.category FROM checkin_checkout c 
     JOIN regular_visitors_vendors r ON c.regular_visitor_id = r.regular_visitor_id 
     WHERE c.flat_id = $flat_id ORDER BY c.check_in_time DESC LIMIT 20"
);
?>

<!DOCTYPE html>
<html>
<head>
    <title>Resident Dashboard - SSS App</title>
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
            margin-right: 10px;
        }
        
        button:hover {
            background: #764ba2;
        }
        
        .approve-btn {
            background: #27ae60;
        }
        
        .reject-btn {
            background: #e74c3c;
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
        }
        
        .badge {
            padding: 5px 10px;
            border-radius: 3px;
            font-size: 12px;
            font-weight: bold;
            color: white;
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
        
        .form-row {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 15px;
        }
        
        .info-card {
            background: #ecf0f1;
            padding: 15px;
            border-radius: 5px;
            margin-bottom: 15px;
        }
        
        .card-title {
            font-weight: bold;
            color: #2c3e50;
            margin-bottom: 5px;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="sidebar">
            <h2>🏠 SSS Resident</h2>
            <div class="nav-item active" onclick="showSection('pending')">Pending Visitors</div>
            <div class="nav-item" onclick="showSection('regular')">Regular Visitors</div>
            <div class="nav-item" onclick="showSection('all-visitors')">View All Visitors</div>
            <div class="nav-item" onclick="showSection('checkins')">Check-in History</div>
            <div class="nav-item" onclick="showSection('maintenance')">Maintenance</div>
            <hr style="margin: 20px 0; opacity: 0.3;">
            <a href="SSS_logout.php" style="color: white; text-decoration: none;">
                <div class="nav-item">Logout</div>
            </a>
        </div>
        
        <div class="main-content">
            <div class="top-bar">
                <div>
                    <h1>Resident Dashboard</h1>
                    <p style="color: #666; margin-top: 5px;">Flat: <?php echo $resident['resident_name']; ?></p>
                </div>
                <span>Welcome, <?php echo $_SESSION['username']; ?></span>
            </div>
            
            <?php if ($message): ?>
                <div class="message"><?php echo $message; ?></div>
            <?php endif; ?>
            
            <!-- Pending Visitors Section -->
            <div id="pending" class="section active">
                <h2>Pending Visitor Requests</h2>
                <?php 
                $pending_count = $pending_visitors->num_rows;
                if ($pending_count > 0):
                ?>
                <table>
                    <tr>
                        <th>Visitor Name</th>
                        <th>Phone</th>
                        <th>Purpose</th>
                        <th>Action</th>
                    </tr>
                    <?php while($row = $pending_visitors->fetch_assoc()): ?>
                    <tr>
                        <td><?php echo $row['visitor_name']; ?></td>
                        <td><?php echo $row['visitor_phone']; ?></td>
                        <td><?php echo $row['purpose_of_visit']; ?></td>
                        <td>
                            <form method="POST" style="display: inline;">
                                <input type="hidden" name="visitor_id" value="<?php echo $row['visitor_id']; ?>">
                                <button type="submit" name="approve_visitor" value="1" class="approve-btn">Approve</button>
                                <input type="hidden" name="action" value="approve">
                            </form>
                            <form method="POST" style="display: inline;">
                                <input type="hidden" name="visitor_id" value="<?php echo $row['visitor_id']; ?>">
                                <button type="submit" name="approve_visitor" value="1" class="reject-btn">Reject</button>
                                <input type="hidden" name="action" value="reject">
                            </form>
                        </td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?>
                <p style="color: #666; padding: 20px; text-align: center;">No pending visitor requests</p>
                <?php endif; ?>
            </div>
            
            <!-- Regular Visitors Section -->
            <div id="regular" class="section">
                <h2>Add Regular Visitor / Vendor</h2>
                <form method="POST">
                    <div class="form-row">
                        <div class="form-group">
                            <label>Visitor Name</label>
                            <input type="text" name="visitor_name" required>
                        </div>
                        <div class="form-group">
                            <label>Phone Number</label>
                            <input type="text" name="visitor_phone" required>
                        </div>
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
                
                <h3 style="margin-top: 30px;">Active Regular Visitors</h3>
                <table>
                    <tr>
                        <th>Name</th>
                        <th>Category</th>
                        <th>Phone</th>
                        <th>Security Code</th>
                    </tr>
                    <?php while($row = $regular_visitors->fetch_assoc()): ?>
                    <tr>
                        <td><?php echo $row['name']; ?></td>
                        <td><?php echo $row['category']; ?></td>
                        <td><?php echo $row['phone_number']; ?></td>
                        <td><strong><?php echo $row['security_code']; ?></strong></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
            </div>
            
            <!-- All Visitors Section -->
            <div id="all-visitors" class="section">
                <h2>All Visitors History</h2>
                <table>
                    <tr>
                        <th>Name</th>
                        <th>Phone</th>
                        <th>Purpose</th>
                        <th>Check-in</th>
                        <th>Check-out</th>
                        <th>Status</th>
                    </tr>
                    <?php while($row = $all_visitors->fetch_assoc()): ?>
                    <tr>
                        <td><?php echo $row['visitor_name']; ?></td>
                        <td><?php echo $row['visitor_phone']; ?></td>
                        <td><?php echo $row['purpose_of_visit']; ?></td>
                        <td><?php echo $row['check_in_time']; ?></td>
                        <td><?php echo $row['check_out_time']; ?></td>
                        <td>
                            <span class="badge badge-<?php echo strtolower($row['approval_status']); ?>">
                                <?php echo $row['approval_status']; ?>
                            </span>
                        </td>
                    </tr>
                    <?php endwhile; ?>
                </table>
            </div>
            
            <!-- Check-in History Section -->
            <div id="checkins" class="section">
                <h2>Regular Visitor Check-in / Check-out History</h2>
                <table>
                    <tr>
                        <th>Visitor Name</th>
                        <th>Category</th>
                        <th>Check-in Time</th>
                        <th>Check-out Time</th>
                        <th>Duration</th>
                    </tr>
                    <?php while($row = $checkins->fetch_assoc()): 
                        $checkin = new DateTime($row['check_in_time']);
                        $checkout = $row['check_out_time'] ? new DateTime($row['check_out_time']) : null;
                        $duration = $checkout ? $checkout->diff($checkin)->format('%H:%I') : 'Still Inside';
                    ?>
                    <tr>
                        <td><?php echo $row['name']; ?></td>
                        <td><?php echo $row['category']; ?></td>
                        <td><?php echo $row['check_in_time']; ?></td>
                        <td><?php echo $row['check_out_time'] ?: 'N/A'; ?></td>
                        <td><?php echo $duration; ?></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
            </div>
            
            <!-- Maintenance Section -->
            <div id="maintenance" class="section">
                <h2>Maintenance Details</h2>
                <table>
                    <tr>
                        <th>Month</th>
                        <th>Amount</th>
                        <th>Due Date</th>
                        <th>Status</th>
                        <th>Payment Mode</th>
                    </tr>
                    <?php while($row = $maintenance->fetch_assoc()): ?>
                    <tr>
                        <td><?php echo $row['billing_month']; ?></td>
                        <td>₹<?php echo $row['maintenance_amount']; ?></td>
                        <td><?php echo $row['due_date']; ?></td>
                        <td>
                            <span class="badge badge-<?php echo strtolower(str_replace(' ', '_', $row['payment_status'])); ?>">
                                <?php echo $row['payment_status']; ?>
                            </span>
                        </td>
                        <td><?php echo $row['payment_mode']; ?></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
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
