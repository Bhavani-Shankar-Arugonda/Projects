<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

session_start();
include 'SSS_db_config.php';


if (!isset($_SESSION['user_id']) || $_SESSION['role'] != 'Resident') {
    header("Location: SSS_login_page.php");
    exit();
}

$message = "";


$resident_id = 0;
$resident_name = "";
$flat_id = 0;

$resident_query = "SELECT * FROM resident_details WHERE user_id = " . $_SESSION['user_id'];
$resident_result = $conn->query($resident_query);

if ($resident_result && $resident_result->num_rows > 0) {
    $resident = $resident_result->fetch_assoc();
    $resident_id = $resident['resident_id'];
    $resident_name = $resident['resident_name'];
    $flat_id = $resident['flat_id'];
} else {
    die("Error: Resident record not found");
}


if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['approve_visitor'])) {
    $visitor_id = $_POST['visitor_id'];
    $action = $_POST['action'];
    
    $status = ($action == 'approve') ? 'Approved' : 'Rejected';
    $sql = "UPDATE visitor_details SET approval_status = '$status', approved_by = $resident_id WHERE visitor_id = $visitor_id";
    
    if ($conn->query($sql)) {
        $message = "✓ Visitor request updated!";
    }
}


if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['add_regular_visitor'])) {
    $v_name = mysqli_real_escape_string($conn, $_POST['visitor_name']);
    $v_phone = mysqli_real_escape_string($conn, $_POST['visitor_phone']);
    $v_category = mysqli_real_escape_string($conn, $_POST['category']);
    $security_code = strtoupper(substr(md5(time() . rand()), 0, 8));
    
    $sql = "INSERT INTO regular_visitors_vendors (name, phone_number, category, security_code, is_active) 
            VALUES ('$v_name', '$v_phone', '$v_category', '$security_code', 1)";
    
    if ($conn->query($sql)) {
        $message = "✓ Regular visitor added! Code: <strong>" . $security_code . "</strong>";
    } else {
        $message = "Error: " . $conn->error;
    }
}


$pending_visitors = $conn->query("SELECT * FROM visitor_details WHERE flat_id = $flat_id AND approval_status = 'Pending' ORDER BY visitor_id DESC");

$all_visitors = $conn->query("SELECT * FROM visitor_details WHERE flat_id = $flat_id ORDER BY visitor_id DESC");

$regular_visitors = $conn->query("SELECT * FROM regular_visitors_vendors WHERE is_active = 1 ORDER BY regular_visitor_id DESC");

$maintenance = $conn->query("SELECT * FROM maintenance_details WHERE flat_id = $flat_id ORDER BY billing_month DESC");

$checkins = $conn->query("SELECT c.*, r.name, r.category FROM checkin_checkout c JOIN regular_visitors_vendors r ON c.regular_visitor_id = r.regular_visitor_id WHERE c.flat_id = $flat_id ORDER BY c.check_in_time DESC LIMIT 20");
?>

<!DOCTYPE html>
<html>
<head>
    <title>Resident Dashboard - SSS App</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { font-family: Arial, sans-serif; background: #f5f5f5; }
        .container { display: flex; min-height: 100vh; }
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
        input, select { width: 100%; padding: 10px; border: 1px solid #ddd; border-radius: 5px; }
        button { background: #667eea; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; margin-right: 10px; }
        button:hover { background: #764ba2; }
        .approve-btn { background: #27ae60; }
        .reject-btn { background: #e74c3c; }
        .message { padding: 15px; background: #d4edda; color: #155724; border: 1px solid #c3e6cb; border-radius: 5px; margin-bottom: 20px; }
        table { width: 100%; border-collapse: collapse; margin-top: 20px; }
        th, td { padding: 12px; text-align: left; border-bottom: 1px solid #ddd; }
        th { background: #f9f9f9; font-weight: bold; }
        .badge { padding: 5px 10px; border-radius: 3px; font-size: 12px; font-weight: bold; color: white; }
        .badge-pending { background: #f39c12; }
        .badge-approved { background: #27ae60; }
        .badge-rejected { background: #e74c3c; }
        .form-row { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; }
        h2 { color: #2c3e50; margin-bottom: 20px; }
        .empty-msg { color: #7f8c8d; padding: 20px; text-align: center; }
        a { text-decoration: none; color: white; }
    </style>
</head>
<body>
    <div class="container">
        <div class="sidebar">
            <h2> SSS Resident</h2>
            <div class="nav-item active" onclick="showSection('pending')">Pending Visitors</div>
            <div class="nav-item" onclick="showSection('regular')">Regular Visitors</div>
            <div class="nav-item" onclick="showSection('all-visitors')">All Visitors</div>
            <div class="nav-item" onclick="showSection('checkins')">Check-in History</div>
            <div class="nav-item" onclick="showSection('maintenance')">Maintenance</div>
            <hr style="margin: 20px 0; opacity: 0.3;">
            <a href="SSS_logout.php"><div class="nav-item">Logout</div></a>
        </div>
        
        <div class="main-content">
            <div class="top-bar">
                <div>
                    <h1>Resident Dashboard</h1>
                    <p style="color: #666; margin-top: 5px;">Resident: <?php echo $resident_name; ?></p>
                </div>
                <span>Welcome, <?php echo $_SESSION['username']; ?></span>
            </div>
            
            <?php if ($message): ?><div class="message"><?php echo $message; ?></div><?php endif; ?>
            
            
            <div id="pending" class="section active">
                <h2>Pending Visitor Requests</h2>
                <?php if ($pending_visitors && $pending_visitors->num_rows > 0): ?>
                <table>
                    <tr><th>Name</th><th>Phone</th><th>Purpose</th><th>Action</th></tr>
                    <?php while($row = $pending_visitors->fetch_assoc()): ?>
                    <tr>
                        <td><?php echo $row['visitor_name']; ?></td>
                        <td><?php echo $row['visitor_phone']; ?></td>
                        <td><?php echo $row['purpose_of_visit']; ?></td>
                        <td>
                            <form method="POST" style="display:inline;">
                                <input type="hidden" name="visitor_id" value="<?php echo $row['visitor_id']; ?>">
                                <input type="hidden" name="action" value="approve">
                                <button type="submit" name="approve_visitor" class="approve-btn">✓ Approve</button>
                            </form>
                            <form method="POST" style="display:inline;">
                                <input type="hidden" name="visitor_id" value="<?php echo $row['visitor_id']; ?>">
                                <input type="hidden" name="action" value="reject">
                                <button type="submit" name="approve_visitor" class="reject-btn">✗ Reject</button>
                            </form>
                        </td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?><p class="empty-msg">No pending visitor requests</p><?php endif; ?>
            </div>
            
    
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
                <?php if ($regular_visitors && $regular_visitors->num_rows > 0): ?>
                <table>
                    <tr><th>Name</th><th>Category</th><th>Phone</th><th>Security Code</th></tr>
                    <?php while($row = $regular_visitors->fetch_assoc()): ?>
                    <tr>
                        <td><?php echo $row['name']; ?></td>
                        <td><?php echo $row['category']; ?></td>
                        <td><?php echo $row['phone_number']; ?></td>
                        <td><strong style="background: #ecf0f1; padding: 5px 10px; border-radius: 3px;"><?php echo $row['security_code']; ?></strong></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?><p class="empty-msg">No active regular visitors</p><?php endif; ?>
            </div>
            
            
            <div id="all-visitors" class="section">
                <h2>All Visitors History</h2>
                <?php if ($all_visitors && $all_visitors->num_rows > 0): ?>
                <table>
                    <tr><th>Name</th><th>Phone</th><th>Purpose</th><th>Check-in</th><th>Check-out</th><th>Status</th></tr>
                    <?php while($row = $all_visitors->fetch_assoc()): ?>
                    <tr>
                        <td><?php echo $row['visitor_name']; ?></td>
                        <td><?php echo $row['visitor_phone']; ?></td>
                        <td><?php echo $row['purpose_of_visit']; ?></td>
                        <td><?php echo $row['check_in_time']; ?></td>
                        <td><?php echo $row['check_out_time'] ?: '-'; ?></td>
                        <td><span class="badge badge-<?php echo strtolower($row['approval_status']); ?>"><?php echo $row['approval_status']; ?></span></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?><p class="empty-msg">No visitor records</p><?php endif; ?>
            </div>
            
            
            <div id="checkins" class="section">
                <h2>Check-in / Check-out History</h2>
                <?php if ($checkins && $checkins->num_rows > 0): ?>
                <table>
                    <tr><th>Visitor Name</th><th>Category</th><th>Check-in</th><th>Check-out</th></tr>
                    <?php while($row = $checkins->fetch_assoc()): ?>
                    <tr>
                        <td><?php echo $row['name']; ?></td>
                        <td><?php echo $row['category']; ?></td>
                        <td><?php echo $row['check_in_time']; ?></td>
                        <td><?php echo $row['check_out_time'] ?: 'Still Inside'; ?></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?><p class="empty-msg">No check-in records</p><?php endif; ?>
            </div>
            
            
            <div id="maintenance" class="section">
                <h2>Maintenance Details</h2>
                <?php if ($maintenance && $maintenance->num_rows > 0): ?>
                <table>
                    <tr><th>Month</th><th>Amount</th><th>Due Date</th><th>Status</th><th>Mode</th></tr>
                    <?php while($row = $maintenance->fetch_assoc()): ?>
                    <tr>
                        <td><?php echo $row['billing_month']; ?></td>
                        <td>₹<?php echo $row['maintenance_amount']; ?></td>
                        <td><?php echo $row['due_date']; ?></td>
                        <td><span class="badge badge-<?php echo strtolower(str_replace(' ', '_', $row['payment_status'])); ?>"><?php echo $row['payment_status']; ?></span></td>
                        <td><?php echo $row['payment_mode']; ?></td>
                    </tr>
                    <?php endwhile; ?>
                </table>
                <?php else: ?><p class="empty-msg">No maintenance records</p><?php endif; ?>
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