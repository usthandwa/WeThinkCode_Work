<?php

/* Getting file name */
$filename = $_FILES['file']['name'];

/* Location */
$location = "uploads/" . $filename;
$uploadOk = 1;
$imageFileType = pathinfo($location, PATHINFO_EXTENSION);


$i = 1;
while (file_exists($location)) {
    $location = "uploads/" . $filename . $i++ . "." . $imageFileType;
}

/* Valid Extensions */
$valid_extensions = array("jpg", "jpeg", "png", "gif");
/* Check file extension */
if (!in_array(strtolower($imageFileType), $valid_extensions)) {
    $uploadOk = 0;
}

if ($uploadOk == 0) {
    echo 0;
} else {
    /* Upload file */
    if (move_uploaded_file($_FILES['file']['tmp_name'], $location)) {
        echo $location;
    } else {
        echo 0;
    }
}
//	session_start();
//	require_once  "../config/conn.php";
//	require "../verify.php";
//	$class = new camagru();
//
//	if (!$class->is_logged_in())
//	{
//		echo "<script>alert('Oops!! looks like you\'re not logged in! click ok to login'); location.href='../login.php' </script>";
//	}
//	else
//		$id = $_SESSION['id'];
//	if (isset($_POST['filter'])){
//		$filepath0 = "overlays/".$_POST['filter'];
//		$dest = imagecreatefrompng($filepath0);
//		imagepng($dest, "temp/image1.png");
//	}
//	else{
//		if (file_exists("temp/image1.png"))
//			unlink("temp/image1.png");
//		$filepath0 = "overlays/clear.png";}
//	$type0 = pathinfo($filepath0, PATHINFO_EXTENSION);
//	$data0 = file_get_contents($filepath0);
//	$image0 = 'data:image/png;' . $type0 . ';base64,' . base64_encode($data0);
//
//    $filename = pathinfo( basename($_FILES["fileToUpload"]["name"]), PATHINFO_FILENAME);
//	$target_dir = "temp/";
//	$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
//	$uploadOk = 1;
//	$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
//
//// Check if image file is a actual image or fake image
//	if(isset($_POST["upload"])) {
//		$err = "";
//		$check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
//		if ($check !== false) {
//			$uploadOk = 1;
//		} else {
//			$err = "File is not an image. ";
//			$uploadOk = 0;
//		}
//// Check if file already exists
//		$i = 1;
//		while (file_exists($target_file)) {
//			$target_file = $target_dir . $filename . $i++ . "." . $imageFileType;
//		}
//// Check file size
//		if ($_FILES["fileToUpload"]["size"] > 5000000) {
//			$err .= " + Sorry, your file is too large.";
//			$uploadOk = 0;
//		}
//// Allow certain file formats
//		if ($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
//			&& $imageFileType != "gif") {
//			$err .= "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
//			$uploadOk = 0;
//		}
//// Check if $uploadOk is set to 0 by an error
//		if ($uploadOk == 0) {
//			$error = $err;
//			echo "<script> alert('Error : ".$error."'); location.href = 'camera.php';</script>";
//			exit;
//// if everything is ok, try to upload file
//		} else {
//			if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
//				$msg = "The file " . basename($_FILES["fileToUpload"]["name"]) . " has been uploaded as " . $target_file . ".";
//				echo "<script> alert('Done : ".$msg."'); location.href = 'camera.php';</script>";
//			} else {
//				$err .= "<br> Sorry, there was an error uploading your file. </br>";
//				echo "<script> alert('Error : ".$err."');location.href = 'camera.php';</script>";
//			}
//		}
//		echo "<script>location.href = 'camera.php';</script>";
//	}