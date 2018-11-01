<?php
	require_once('../config/conn.php');
	require_once('verify.php');
    $exists = new camagru();

    if ($_GET['email']&& $_GET['hash']) {
        $exists->exists($_GET['email'], $_GET['hash']);
    }
?>

    <!DOCTYPE html>
    <html class="page">
    <head>
        <meta http-equiv="Content-Type"
              content="width=device-width, initial scale=1; text/html; charset=utf-8"/>
        <title>CAMAGRU : Sign up</title>
        <link rel="stylesheet" href="../style/style.css" type="text/css"/>
    </head>
    <body>
    <div class="page__demo">
        <div class="main-container page__container">
                <h2 class="header">| CAMAGRU: Sign up |</h2>
                <hr/>
                <form method="POST" enctype="multipart/form-data" ><br>

                <div class="page__section">
                    <label class="field field_type3">
                        <input type="email" name="email" class="field__input" placeholder="e.g. username@domain.com"
                               required/>
                        <span class="field__label-wrap">
						<span class="field__label">Enter your e-mail</span>
					</span>
                    </label>
                </div>
                    <div class="page__section">
                        <label class="field field_type3">
                            <input name="uname" class="field__input" placeholder="must be unique" required/>
                            <span class="field__label-wrap">
						<span class="field__label">Enter your username</span>
					</span>
                        </label>
                    </div>
                <div class="page__section">
                    <label class="field field_type3">
                        <input name="password" type="password" class="field__input" REQUIRED
                               placeholder="Tip: include a number/special character and at least one uppercase">
                        <span class="field__label-wrap">
						<span class="field__label">Enter your password</span>
					</span>
                    </label>
                    <div class="page__section">
                        <label class="field field_type3">
                            <input name="password1" type="password" class="field__input" REQUIRED
                                   placeholder="Tip: same as above">
                            <span class="field__label-wrap">
						<span class="field__label">Confirm your password</span>
					</span>
                        </label>
                    </div>
                    <br/>
                </div>
                <hr/>
                <br/>
                <button type="submit" class="button" name="signup">&nbsp;SIGN UP</button><button type="reset" value="reset" class="button">&nbsp;CANCEL </button>
                <br/><br/>
                <label> | I have an account !! | <a href="login.php">Sign In</a></label>
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
	try {

		if (isset($_POST['signup'])) {
			$email = $_POST['email'];
			$uname = htmlspecialchars($_POST['uname']);
			$password = $_POST['password'];
			$password1 = $_POST['password1'];

			if (!filter_var($email, FILTER_VALIDATE_EMAIL) || empty($email)){
				$error[] = ' Please enter a valid email address !';
			} else if (empty($uname)) {
				$error[] = " passwords do not match, please confirm your password!";
			}else if ($password !== $password1) {
				$error[] = " passwords do not match, please confirm your password!";
			} else if (strlen($password) < 6 || !preg_match('/^(?=.*\d)(?=.*[@#\-_$%^&+=§!\?])(?=.*[a-z])(?=.*[A-Z])[0-9A-Za-z@#\-_$%^&+=§!\?]{6,16}$/', $password)) {
				$error[] = " Password does not meet minimum requirements";
			} else {
				try {

					$stmt = $con->prepare('SELECT email FROM users WHERE email=:email');
					$stmt->execute(array(':email' => $email));
					$row = $stmt->fetch(PDO::FETCH_ASSOC);
					foreach ($row as $rw) {
						if ($rw === $email) {
							$error[] = " sorry email id already taken !";
						}
					}
					$stmt = $con->prepare('SELECT username FROM users WHERE username=:uname');
					$stmt->execute(array(':uname' => $uname));
					$row = $stmt->fetch(PDO::FETCH_ASSOC);
					foreach ($row as $rw) {
						if ($rw === $uname) {
							$error[] = " username must be unique !";;
						}
					}
				} catch (PDOException $e) {
					$error[] = $e->getMessage();
				}
			}
			if (isset($error) && !empty($error)) {
				foreach ($error as $err) {
					echo "<script>alert('ERROR : $err'); location.href='register.php' </script>";
				}
			} else {
				try {
					$hash = MD5(rand(1, 1000));
					$password = serialize(hash('whirlpool', $password1));
					$insert = $con->prepare("INSERT INTO users(email, username, pword, Token)
			VALUES(:email, :uname, :password1, :token)
				");
					$insert->bindParam(':uname', $uname);
					$insert->bindParam(':email', $email);
					$insert->bindParam(':password1', $password);
					$insert->bindParam(':token', $hash);
					$insert->execute();

					$exists->verify($email, $password1, $hash);
					} catch (PDOException $e) {
					$err = "Error: " . $e->getMessage();
					echo "<script>alert('ERROR : $err'); location.href='register.php' </script>";
				}
			}
		}
	} catch (PDOException $e) {
		$err = "Error: " . $e->getMessage();
		echo "<script>alert('ERROR : $err'); location.href='register.php' </script>";
	}

?>