<!DOCTYPE html>
<html class="page">
<head>
    <meta http-equiv="Content-Type"
          content="width=device-width, initial scale=1; text/html; charset=utf-8"/>
    <title>CAMAGRU : Login</title>
    <link rel="stylesheet" href="../style/style.css" type="text/css"/>
</head>
<body>
<div class="page__demo">
    <div class="main-container page__container">
        <form method="post">
            <h2 class="header">| CAMAGRU: Log-in |</h2>
            <hr/>
            <div class="page__section">
                <label class="field field_type3">
                    <input type="text" class="field__input" name="uname" placeholder="Username" required/>
                    <span class="field__label-wrap">
							<span class="field__label">Enter your username</span>
                    </span>
                </label>
            </div>
            <div class="page__section">
                <label class="field field_type3">
                    <input type="password" class="field__input" name="passw" placeholder="Your Password"/>
                    <span class="field__label-wrap">
						<span class="field__label">Enter your password</span>
                    </span>
                </label>
            </div>
            <br/>
            <hr/>
            <br/>
            <button type="submit" name="signin" class="button">&nbsp;SIGN IN</button><button type="reset" value="reset" class="button">&nbsp;Cancel </button>
            <br/><br/>
                <label>| You don't have an account ? |<a href="register.php"> Sign Up </a></label><br><label > | You forgot your password ? |<a href="fpass.php"> Reset Password</a></label>
        </form>
    </div>
</div>
<div class="footer">
    <hr/>
    <strong>@szama #CAMAGRU</strong>
</div>
</body>
</html>

<?php
	session_start();

	include "../config/conn.php";
	if (isset($_POST['signin'])) {
		try {
			if (!empty($_POST['uname']) && !empty($_POST['passw'])) {

				$uname = htmlspecialchars($_POST['uname']);
				$password = $_POST['passw'];
				$one = 1;
				$hash_password = serialize(hash('whirlpool', $password));
				$select = $con->prepare("SELECT * FROM users WHERE username= :uname AND pword = :pword");
				$select->execute(['uname' => $uname, 'pword' => $hash_password]);
				$result = $select->fetch(PDO::FETCH_ASSOC);

				if ($select->rowCount()) {
					if ($result['Verify'] == $one) {
						foreach ($result as $row) {
							$fname = $result['username'];
							$email = $result['email'];
							$id = $result['userid'];
						}
						$_SESSION['email'] = $email;
						$_SESSION['fname'] = $fname;
						$_SESSION['id'] = $id;


						header("location:../images/camera.php");
					} else {
                        echo "<script>alert('Please activate your account, using your e-mail link'); location.href = '?inactive' </script>";
						exit;
					}
				} else
					echo "<script>alert('Incorrect username/password') </script>";
			}

		} catch (PDOException $e) {

			echo "Error: <br/>" . $e->getMessage();
		}
	}

?>