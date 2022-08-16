<?php
session_start();
    //Connect to database
    require'connectDB.php';
//**********************************************************************************************

    //Get current date and time
    date_default_timezone_set('Asia/Damascus');
    $d = date("Y-m-d");

    $Tarrive = mktime(07,30,00);
    $TimeArrive = date("H:i:sa", $Tarrive);
//**********************************************************************************************
    $Tleft = mktime(10,30,00);
    $Timeleft = date("H:i:sa", $Tleft);

    if (!empty($_POST['seldate'])) {
        $seldate = $_POST['date'];
    }
    else{
        $seldate = $d;
      }

    $_SESSION["exportdata"] = $seldate;
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Users Logs</title>
<script src="https://code.jquery.com/jquery-3.3.1.js"
        integrity="sha1256-2Kok7MbOyxpgUVvAk/HJ2jigOSYS2auK4Pfzbm7uH60="
        crossorigin="anonymous">
</script>
<script src="js/jquery.min.js"></script>
<script>
  $(document).ready(function(){
    setInterval(function(){
      $.ajax({
        url: "load-users.php"
        }).done(function(data) {
        $('#cards').html(data);
      });
    },3000);
  });
</script>
<style>

body {
    background-image: url(image/bg.png);
    background-repeat: no-repeat;
    background-size: cover;
}


header .head h1 {
    font-family:aguafina-script;
    text-align: 
    center;color:#fff;
}
header .head img {
    float: left;
}
header .opt {
    float: right;
    margin: -100px 20px 0px 0px
}

header .opt button {
    padding: 7px;
    background-color: #0d6bfd;
    color: #fff;
    border: none;
    border-radius: 5px;
    margin-right: 20px;
}

header .opt button:hover {
    background-color: #1ab0e5;
}

#logout {
    padding: 7px;
    background-color: #dc3545;
    color: #fff;
    border: none;
    border-radius: 5px;
    margin-right: 20px;
}

#logout:hover {
    background-color: #f76f72;
}

#yellow {
    padding: 7px;
    background-color:yellowgreen;
    color: #fff;
    border: none;
    border-radius: 5px;
    margin-right: 20px;
}

#yellow:hover {
    background-color: yellow;
}

header .opt #inp {
    padding-left:5px;
    margin:2px 0px 10px 3px;
    border-radius:7px; 
    background-color:#fff; 
    color: #333;
}

header .opt p {
    text-align: left;
    font-size:19px;
    color:#fff;
    margin-top: 50px;
}
.export {
    margin: 0px 0px 10px 20px; 
    background-color:#900C3F ;
    font-family:cursive;
    border-radius: 7px;width: 145px;
    height: 28px;color: #ffffcc; 
    border-color: #ffffcc;
    font-size:
    17px
}
.export:hover {
    cursor: pointer;
    background-color:#C70039
}

#table {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
    margin-top: 10px;
}

#table td, #table th {
    border: 1px solid #ddd;
    padding: 8px;
     opacity: 0.6;
}

#table tr:nth-child(even){
    background-color: #f2f2f2;
}
#table tr:nth-child(odd){
    background-color: #f2f2f2;
    opacity: 0.9;
}

#table tr:hover {
    background-color: #ddd; 
    opacity: 0.8;
}

#table th {
	 opacity: 0.6;
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #00A8A9;
    color: white;
}
</style>
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-0evHe/X+R7YkIZDRvuzKMRqM+OrBnVFBL6DOitfPri4tjfHxaWutUpFmBp4vmVor" crossorigin="anonymous">
</head>
<body class="p-3 mb-2 bg-secondary  text-dark">
<header >

	<div class="head">
        <button id="yellow" onclick="location.href='water.php'">Notification</button>
        <button id="logout" onclick="location.href='logout.php'">Logout</button>
		<h1> <br> </h1>
	</div>

	<div class="opt">
		<table border="0">
			<tr>
				<td ><button onclick="location.href='AddCard.php'">Add New Student</button></td>
				<td><p>Select the date log:
				<form method="POST" action="">
					<input type="date" name="date" id="inp"><br>
					<input style="margin-top: 10px" #id="inp-2" class="btn btn-success" type="submit" name="seldate" value="View Attendance">
				</form>
				</p></td>
			</tr>
		</table>
	</div>
</header>
<h4 style="margin-left: 15px; margin-bottom: 30px; color:#fff;">
  Time to arrive :  <?php echo $TimeArrive?> <br>
  Time to leave :     <?php echo $Timeleft?>
</h4>

<form method="post" action="export.php">
  <input class="btn btn-info text-white" type="submit" name="export" value="Export to Excel" />
</form>
<div id="cards" class="cards">
</div>

<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/js/bootstrap.bundle.min.js" integrity="sha384-pprn3073KE6tl6bjs2QrFaJGz5/SUsLqktiwsUTF55Jfv3qYSDhgCecCxMW52nD2" crossorigin="anonymous"></script>
</body>
</html>
