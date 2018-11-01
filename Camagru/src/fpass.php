<?php
session_start();
require_once '../config/conn.php';
if(isset($_GET['id']) && isset($_GET['code']))
{
    $id = $_GET['id'];
    $code = $_GET['code'];
    echo "<script>location.href='resetpass.php?id=$id&code=$code'</script>";
}

if(isset($_POST['btn-submit']))
{
	$email = $_POST['txtemail'];
	try {
        $url = $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI'];
		$stmt = $con->prepare("SELECT userid FROM users WHERE email=:email LIMIT 1");
		$stmt->execute(array(":email" => $email));
		$row = $stmt->fetch(PDO::FETCH_ASSOC);
		if ($stmt->rowCount() > 0) {
			$id = base64_encode($row['userid']);
			$code = md5(uniqid(rand()));

			$stmt = $con->prepare("UPDATE users SET Token=:token WHERE email=:email");
			$stmt->execute(array(":token" => $code, "email" => $email));

			echo $message = "
				   Hello , $email

				   We got requested to reset your password, if you do this then just click the following link to reset your password, if not just ignore this email,

				   Click Following Link To Reset Your Password

				   http://$url?id=$id&code=$code' << click here to reset your password

				   thank you :)
				   ";
			$subject = "Password Reset";
			$header = 'From:noreply@camagru.com' . "\r\n";

			mail($email, $subject, $message, $header);

				echo "<script>alert('Success! We sent an email to $email ' +
					 'Please click on the password reset link in the email to generate new password.');</script>";


		} else {
            echo "<script>alert('Sorry! No Account Found : You can Signup'); location.href='register.php' </script>";
		}
	}
	catch (PDOException $e)
    {
        echo "<script>alert('Error: $e'); location.href='register.php' </script>";
    }
}
?>

<!DOCTYPE html>
<html class="page">
  <head>
    <title>Forgot Password</title>
    <link href="../style/style.css" rel="stylesheet" media="screen">
  </head>
  <body id="">
    <div class="row page__container">

      <form class="field__input" method="post">
        <h2 class="">Forgot Password</h2><hr />
          <div class='alert alert-info'>
              Please enter your email address. You will receive a link to create a new password via email.! <br>
          </div>
          <div class="page__section">
              <label class="field field_type3">
                  <input type="email" class="field__input" name="txtemail" placeholder="Enter e-mail" required/>
                  <span class="field__label-wrap">
							<span class="field__label">Enter your username</span>
                    </span>
              </label>
          </div>
     	<hr />
        <button class="button" type="submit" name="btn-submit">Generate new Password</button>
      </form>

    </div>

  </body>
</html>