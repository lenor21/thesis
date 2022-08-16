<?php
require 'conn2.php';
$_SESSION = [];
session_unset();
session_destroy();
header("Location: index.php");
?>