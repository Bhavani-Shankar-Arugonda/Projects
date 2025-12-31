<?php
session_start();
session_destroy();
header("Location: SSS_login_page.php");
exit();
?>
