<?php
session_start();
    $uid = $_SESSION['fname'];
require "../config/conn.php";

if (isset($_POST['delete'])) {


	$id = $_POST['delete'];
	//UNCOMMENT SCRIPT BELOW TO CHECK VALUE SENT THROUGH TO DB TO BE DELETED
//	echo "<script> alert('This is image id to delete $id, and user $uid.');</script>";

	$stmt = $con->prepare('SELECT picname FROM images WHERE imageid=:id');
	$stmt->execute(['id' => $id]);
	$row = $stmt->fetch(PDO::FETCH_ASSOC);
	unlink("uploads/" . $row['picname']);
	$stmt = $con->prepare("DELETE FROM images WHERE imageid=:id");
	$stmt->execute(['id' => $id]);


	if ($stmt->rowCount()) {
		echo "<script> alert('Your image with id $id has been deleted.'); location.href='camera.php';</script>";
	} else
		echo "<script> alert('Unable to delete image. this is id/delete $id, and user $uid.'); location.href='../index.php'; </script>";
}
else
    echo "<script> alert('oops. something went wrong. This is posted id/delete $id, and user $uid.'); location.href='../index.php'; </script>";
?>