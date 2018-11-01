<?php
session_start();
if(!empty($_SESSION['id'])) {
        $id = trim($_SESSION['id']);
        $msg =
            "Hello " . $_SESSION['fname'] . " welcome to your profile." . "<br>" . "
            <p> You can change your details here </p>";
        Try{
            require "../config/conn.php";
            $stmt = $con->prepare("SELECT * FROM users WHERE userid = $id");
            $stmt->execute();

            if ($stmt->rowCount()) {
	            $row = $stmt->fetch();
	            $print_pw = $row['pword'];
            } else
                echo "<script>alert('Something didn\'t go as expected, try again.'); location.href='profile.php';</script>";

            if (isset($_POST['submit'])) {
	            $errorString = "";

	            $username = htmlentities(strip_tags(trim($_POST['uname'])));
	            $username = htmlentities(strip_tags($username));
	            if (empty($username)) {
		            $errorString = $errorString . "Please enter a username.";
		            //remove any slashes that are automatically added
		            $username = htmlentities(strip_tags($username));
	            }

	            $notif = $_POST['chkbox'];

                $password = trim($_POST['pass']);
	            $pass_conf = trim($_POST['confirmpass']);
	            if (!empty($password)) {
		            if ($pass_conf === "") {
			            $errorString = " passwords do not match, please confirm your password!";
		            } else if ($password !== $pass_conf) {
			            $errorString = " passwords do not match, please confirm your password!";
		            } else if (strlen($password) < 6 || !preg_match('/^(?=.*\d)(?=.*[@#\-_$%^&+=§!\?])(?=.*[a-z])(?=.*[A-Z])[0-9A-Za-z@#\-_$%^&+=§!\?]{6,16}$/', $password)) {
			            $errorString = " Password does not meet minimum requirements";
		            } else {
			            $hash = MD5(rand(1, 1000));
			            $password = serialize(hash('whirlpool', $pass_conf));
		            }
	            }

	            $email = htmlentities(strip_tags(trim($_POST['email'])));
	            if (!filter_var($email, FILTER_VALIDATE_EMAIL) || empty($email)) {
		            $errorString = " Please enter a valid email address !";
	            }
	            if (empty($email)) {
		            $errorString = $errorString . "Please enter email address ";
		            $email = htmlentities(strip_tags($email));
	            }

	            // check if there were any errors

	            if (empty($errorString)) {//No errors, update the data
                    if (strcmp($username, $row['username']) || strcmp($email, $row['email']) || strcmp($password, $print_pw) || $notif != $row['notif']) {
                        if  (empty($password)) {
                            $query = $con->prepare("UPDATE users SET username = '$username', email = '$email', notif = '$notif' WHERE userid = $id")->execute();
                        }
                        else {
                            $query = $con->prepare("UPDATE users SET username = '$username', email = '$email', pword = '$password' , notif = '$notif' WHERE userid = $id")->execute();
                        }
	                    if (!$query) {//if there was a problem - get the error message and go back
		                    echo "<script>alert('Error!! changes not made: '); location.href = 'profile.php'; </script>";
		                    exit;
	                    }else
	                    echo "<script>alert('Congrats!! changes accepted'); location.href = 'profile.php'; </script>";
                    } else {
                    echo "<script>alert('Eish!! didn\'t get any changes, wanna try that again?'); location.href = 'profile.php'; </script>";
//			            header("Location: profile.php");
		            }
	            } else {//There were errors
		            echo "<script>alert('Oops!! looks like you\'ve made a tiny mistake: $errorString'); </script>";
	            }
            }

	?>
    <!DOCTYPE html>
<html class="page">

<head>
	<meta http-equiv="Content-Type" content="width=device-width, initial scale=1; text/html; charset=utf-8" />
	<title>CAMAGRU : User Profile</title>
	<link rel="stylesheet" href="../style/style.css" type="text/css" />
</head>

<body>
	<div class="demo-wrapper">
		<ul class="navbar">
			<li><a href="../images/camera.php">Home</a></li>
			<li><a class="active" href="profile.php">Profile</a></li>
			<li><a href="../images/Gallery.php">Gallery</a></li>
			<li style="float: right"><a href="logout.php">LogOut</a></li>
		</ul>
		<div class="main-container page__container">
			<h2 class="header">| CAMAGRU: Profile |</h2>
			<hr/>
			<br>
			<?php echo $msg ?>
			<br>
			<form method="POST" action="#" enctype="multipart/form-data">
				<table style="width:60%; margin:0">
					<td>
						<div class="page__section">
							<label class="field field_type3">
                                <input name="uname" class="field__input"
                                       value="<?php echo $row['username']; ?>"
                                       placeholder="change username" />
                                <span class="field__label-wrap">
						            <span class="field__label">Enter your username</span>
					            </span>
                            </label>
						</div>
						<div class="page__section">
							<label class="field field_type3">
                                <input type="email" name="email"
                                       class="field__input"
                                       value="<?php echo $row['email']; ?>"
                                       placeholder="Change your e-mail"/>
                                <span class="field__label-wrap">
						<span class="field__label">Enter your e-mail</span>
					</span>
                            </label>
						</div>
						<div class="page__section">
							<label class="field field_type3">
                            <input name="pass" type="password" class="field__input"
                                   placeholder="New Password" >
                            <span class="field__label-wrap">
						<span class="field__label">Enter your password</span>
					</span>
                        </label>
						</div>
						<div class="page__section">
							<label class="field field_type3">
                            <input name="confirmpass" type="password" class="field__input"
                                   placeholder="Tip: same as above">
                            <span class="field__label-wrap">
						<span class="field__label">Confirm your password</span>
					</span>
                        </label>
							<br>
							<label class="field field_type3"> Enable e-mail notification
                            <input type="hidden" name="chkbox" value="0" />
                            <input type="checkbox" name="chkbox" value="1" <?php if($row['notif'] == 1) echo "checked"; ?> /></label>
							<br>
							<button type="submit" name="submit" class="button" style="width: 50%; padding-top: 2%" value="Submit">Save
                        </button><button class="button" style="width: 50%; padding-top: 2%; " type="reset" value="reset">Clear
                        </button>
						</div>
					</td>
				</table>
			</form>
		</div>
	</div>
    <div class="footer">
        <hr/>
        <strong>@szama #CAMAGRU</strong>
    </div>
</body>

</html>
<?PHP
    }
    catch (PDOException $e){
            $e = $e->getMessage();
    echo "<script>alert('Oops!! looks like you\'ve managed to break something: $e '); </script>";

    }
}
else
	echo "<script>alert('Oops!! looks like you\'re not logged in! Please login'); location.href='login.php' </script>";
?>