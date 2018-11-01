<?php
session_start();
	session_unset();
session_destroy();
?>

<!DOCTYPE html>
<html class="page">
<head>
	<meta http-equiv="Content-Type"
	      content="width=device-width, initial scale=1; text/html; charset=utf-8"/>
	<title>CAMAGRU : Sign Out</title>
	<link rel="stylesheet" href="../style/style.css" type="text/css"/>
</head>
<body>
<div class="page__demo">
	<div class="main-container page__container">
		<h2 class="header">| CAMAGRU: Sign Out |</h2>

		<p>Sad to see you leave so soon :(</p>
		<p>If that was unintentional <a href ="../index.php">click here</href></a> you will be take to the login page</p>
        <p>else you'll be redirect to public Gallery</p>

	</div>
</div>
</body>
</html>
<?PHP
header("refresh:10;location:../index.php");
