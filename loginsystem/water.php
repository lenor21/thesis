<!DOCTYPE html>
<html>
   <script type="text/javascript" src="js/jquery.min.js"></script>
    <script type="text/javascript" src="js/jquery-3.1.1.min.js"></script>
    <script type="text/javascript" src="js/jquery-3.6.0.min.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" />
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
	
<head>
<script>
         $(document).ready(function(){
             setInterval(() => {
                $.ajax({
                    url: 'get.php',
                    type: 'post',
                    success: function(response){
                       
                  $(".handle").css({"width" : response});
                      
                    }
                });
             }, 1000);
         });
     </script>
	<style>
	.bar {
  -webkit-transition: width 0.5s ease !important;
     -moz-transition: width 0.5s ease !important;
       -o-transition: width 0.5s ease !important;
          transition: width 0.5s ease !important;
}

		body {
    background-image: url(image/bg.png);
    background-repeat: no-repeat;
    background-size: cover;
}
		p {
			font-size: 20px;
		}
	
		.container {
			background-color: rgb(192, 192, 192);
			width: 98%;
				border-radius: 15px;
				position: absolute;
				top:36%;
		}
	
		.skill {
			background-color: rgb(116, 194, 92);
			color: white;
			padding: 1%;
			text-align: right;
			font-size: 20px;
				
		}
	
		.html {
			width: 80%;
		}
	
		.php {
			width: 60%;
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
	</style>
</head>

<body>
	<br>
	<nav class="navbar navbar-inverse">
    <div class="container-fluid">
     <div class="navbar-header">
      <a class="navbar-brand" href="#">High Temperature Students</a>
     </div>
     <ul class="nav navbar-nav navbar-right">
      <li class="dropdown">
       <a href="#" class="dropdown-toggle" data-toggle="dropdown"><span class="label label-pill label-danger count" style="border-radius:10px;"></span> <span class="glyphicon glyphicon-envelope" style="font-size:18px;"></span></a>
       <ul class="dropdown-menu"></ul>
      </li>
     </ul>
    </div>
   </nav>
	<center><h1 style="color:blue;">Sanitizer Storage Level</h1></center>
	<div class="container">
		<div id="Mname"  class="skill handle bar">CM</div>
	</div>
<img src="ruler_PNG82.png" style="position: absolute;  top: 0%;" alt="Nature" class="responsive" width="98%" height="420">

	

</body>
</html>

<script>
$(document).ready(function(){
 
 function load_unseen_notification(view = '')
 {
  $.ajax({
   url:"fetch.php",
   method:"POST",
   data:{view:view},
   dataType:"json",
   success:function(data)
   {
    $('.dropdown-menu').html(data.notification);
    if(data.unseen_notification > 0)
    {
     $('.count').html(data.unseen_notification);
    }
   }
  });
 }
 
 load_unseen_notification();
 
 $('#comment_form').on('submit', function(event){
  event.preventDefault();
  if($('#subject').val() != '' && $('#comment').val() != '')
  {
   var form_data = $(this).serialize();
   $.ajax({
    url:"insert.php",
    method:"POST",
    data:form_data,
    success:function(data)
    {
     $('#comment_form')[0].reset();
     load_unseen_notification();
    }
   });
  }
  else
  {
   alert("Both Fields are Required");
  }
 });
 
 $(document).on('click', '.dropdown-toggle', function(){
  $('.count').html('');
  load_unseen_notification('yes');
 });
 
 setInterval(function(){ 
  load_unseen_notification();; 
 }, 5000);
 
});
</script>
