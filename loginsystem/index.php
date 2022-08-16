<?php
require 'conn2.php';

/*if(!empty($_SESSION["id"])){
  header("Location: index.php");
}*/
if(isset($_POST["submit"])){
	$usernameemail = $_POST["usernameemail"];
	$password = $_POST["password"];
	$result = mysqli_query($conn, "SELECT * FROM tb_user WHERE username = '$usernameemail'");
	$row = mysqli_fetch_assoc($result);
	if(mysqli_num_rows($result) > 0){
		if($password == $row['password']){
			$_SESSION["login"] = true;
			$_SESSION["id"] = $row["id"];
			header("Location:view.php");
		}
		else{
			echo
			"<script> alert('Wrong Password'); </script>";
		}
	}
	else{
		echo
		"<script> alert('User Not Registered'); </script>";
	}
}
 ?>


<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Login</title>
	<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
	<div class="container">
		<div class="container-box">
			<form action="" method="post" autocomplete="off">
				<h1>Login</h1>
				<label for="usernameemail">Username</label><br>
				<input type="text" name="usernameemail" id = "usernameemail" required value=""><br>
				<label for="password">Password</label><br>
				<input type="password" name="password" id = "password" required value=""><br>
				<div class="flex">
					<button class="submit" type="submit" name="submit">Login</button>
					<button class="register" onclick="location.href='new_account.php'"><a href="new_account.php">Register</a></button>
				</div>
			</form>
		</div>
	</div>
</body>
</html>