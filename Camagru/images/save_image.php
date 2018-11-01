<?php
session_start();
if (!empty($_SESSION['id'])) {
	require_once('../config/conn.php');

	if (isset($_POST['save'])) {
		try {
		    if (!empty($_POST['up-image']))
			    $data = substr($_POST['up-image'], strpos($_POST['up-image'], ",") + 1);
		    else
                $data = substr($_POST['sub-image'], strpos($_POST['sub-image'], ",") + 1);
			$decodedData = base64_decode($data);
			$fp = fopen("temp/canvas.png", 'wb');
			if (!fwrite($fp, $decodedData)) {
				die ("<script>alert('Unable to find image. Please upload/take an image.'); location.href='camera.php';</script>");
			}
			fclose($fp);
		} catch (Exception $e) {
			echo $data . "<br>" . $e->getMessage() . "<script>location.href='camera.php';</script>";
		}

		$sub_image = "temp/canvas.png";
		$filter = "temp/image1.png";
		if (!file_exists($filter) && !empty($_POST['sub-image']))
			echo "<script> location.href='camera.php'; alert('Please select filter to proceed'); </script>";
		else
		    $filter = file_exists($filter) ? $filter : "overlays/clear.png";
		if (file_exists($filter) && file_exists($sub_image)) {
			try {
				$dest = imagecreatefrompng($sub_image);
				$src = imagecreatefrompng($filter);
				imagecopymerge($dest, $src, 200, 20, 0, 0, 150, 150, 100);
				//RED - imagecopy(address of dest, address of src, 17, 13, 0, 0, w of src, h of src)
				$imageName = "img" . time() . ".png";
				$pic_ = "uploads/" . $imageName;
				imagepng($dest, $pic_);
				move_uploaded_file($imageName, $pic_);
				$user_id = $_SESSION['id'];

				$query = $con->prepare("INSERT INTO images (picname, piclocation, userid) VALUES ('$imageName', '$pic_', '$user_id')");
				$query->execute();
				imagepng($dest, "temp/img.png");
				echo "<script> '$pic_' </script>";

			} catch (PDOException $e) {
				echo "Caught exception:  " . $e->getMessage() . "<script>location.href='camera.php';</script>";
			}
			echo "<script>location.href='camera.php';</script>";
		} else {
			echo "<script> alert('Oooops'); location.href='camera.php';) </script>";
			die();
		}
		imagedestroy($dest);
		imagedestroy($src);
	}
}
else
    echo "<script>alert('Some functions need you to log-in.'); location.href='camera.php';</script>";
	?>
