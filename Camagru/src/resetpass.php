<?php
require_once 'config/conn.php';

if(empty($_GET['id']) && empty($_GET['code']))
{
	echo "<script>location.href='index.php' </script>";
}

if(isset($_GET['id']) && isset($_GET['code']))
{
	$id = base64_decode($_GET['id']);
	$code = $_GET['code'];

	$stmt = $con->prepare("SELECT * FROM users WHERE userid=:uid AND Token=:token");
	$stmt->execute(array(":uid"=>$id,":token"=>$code));
	$rows = $stmt->fetch(PDO::FETCH_ASSOC);

	if($stmt->rowCount() > 0)
	{
		if(isset($_POST['btn-reset-pass']))
		{
			$pass = $_POST['pass'];
			$cpass = $_POST['confirm-pass'];

			if($cpass!==$pass)
			{
				$msg = "<div class='alert alert-block'>
						<button class='close' data-dismiss='alert'>&times;</button>
						<strong>Sorry!</strong>  Password Doesn't match. 
						</div>";
			}
			else
			{
				$password = serialize(hash('whirlpool', $cpass));
				$stmt = $con->prepare("UPDATE users SET pword=:upass WHERE userid=:uid");
				$stmt->execute(array(":upass"=>$password,":uid"=>$rows['userid']));

				$msg = "<div class='alert alert-success'>
						<button class='close' data-dismiss='alert'>&times;</button>
						Password Changed.
						</div>";
				header("refresh:5;index.php");
			}
		}
	}
	else
	{
		$msg = "<div class='alert alert-success'>
				<button class='close' data-dismiss='alert'>&times;</button>
				No Account Found, Try again
				</div>";

	}
	
	
}

?>
<!DOCTYPE html>
<html>
  <head class="header">
    <title>Password Reset</title>
    <link href="../style/style.css" rel="stylesheet" media="screen">
  </head>
  <body id="login">

    <div class="page__demo page__container">
    	<div class='alert alert-success'>
			<strong>Hello !</strong>  <?php echo $rows['username'] ?> you are here to reset your forgetton password. <br>
		</div>
        <form class="page__section" method="post">
        <h3 class="">Password Reset.</h3><hr />
        <?php
        if(isset($msg))
		{
			echo $msg;
		}elseif (!strcmp($msg, "Password Changed")){
            echo "<script> alert ('Password changed, you can now log in'); location.href = 'index.php'; </script>";
        }
		else {
		?>
            <div class="page__section">
                <label class="field field_type3">
                    <input name="pass" type="password" class="field__input" REQUIRED
                           placeholder="New Password" >
                    <span class="field__label-wrap">
						<span class="field__label">Enter your password</span>
					</span>
                </label>
            </div>
                <div class="page__section">
                    <label class="field field_type3">
                        <input name="confirm-pass" type="password" class="field__input" REQUIRED
                               placeholder="Tip: same as above">
                        <span class="field__label-wrap">
						<span class="field__label">Confirm your password</span>
					</span>
                    </label>
                </div>
            	<hr />
        <button class="button" type="submit" name="btn-reset-pass">Reset Your Password</button>
        <?php } ?>
      </form>

    </div>
    <div class="footer">
        <hr/>
        <strong>@szama #CAMAGRU</strong>
    </div>
  </body>
</html>