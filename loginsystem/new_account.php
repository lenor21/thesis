<?php 
require 'conn2.php';

if(isset($_POST["submit"])) {
	$fullname = $_POST["fullname"];
	$username = $_POST["username"];
	//$email = $_POST["email"];
	$password = $_POST["password"];
	$confirmpassword = $_POST["confirmpassword"];
	$duplicate = mysqli_query($conn, "SELECT * FROM tb_user WHERE username = '$username'");
	if(mysqli_num_rows($duplicate) > 0) {
		echo 
		"<script> alert('Username or Email has already taken')</script>";
	}
	else {
		if ($password == $confirmpassword) {
			$query = "INSERT INTO tb_user VALUES('', 'fullname', '$username', '$password')";
			mysqli_query($conn, $query);
			echo 
			"<script> alert('Registration Successful')</script>";
		}
		else {
			echo 
			"<script> alert('Password does not match')</script>";
		}
	}
}

 ?>


<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Registration</title>
	<link rel="stylesheet" type="text/css" href="register.css">
</head>
<body>
	<div class="container">
		<div class="register-box">
			<form action="" method="post" autocomplete="off">
				<h1>Registration</h1>
				<label for="fullname">Fullname</label><br>
				<input type="text" name="fullname" required value=""><br>
				<label for="username">Username</label><br>
				<input type="text" name="username" required value=""><br>
				<label for="password">Password</label><br>
				<input type="password" name="password" required value=""><br>
				<label for="confirmpassword">Confirm Password</label><br>
				<input type="password" name="confirmpassword" required value=""><br>
				<div class="flex">
					<button class="submit" type="submit" name="submit">Register</button><br>
					<button class="register" onclick="location.href='index.php'"><a href="index.php">Login</a></button>
				</div>
			</form>
		</div>
	</div>
</body>
</html>