<?php
	class camagru
	{
		public function verify($email, $password, $hash)
		{
			function get_starred($str) {
				$len = strlen($str);
				return substr($str, 0, 1).str_repeat('*', $len - 2).substr($str, $len - 1, 1);
			}
			$password1 = get_starred($password);
		    $url = $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI'];
		    try {
				$to = $email;
				$subject = 'Signup | Verification';
				$message = '

				Thanks for signing up!
				Your account has been created,
				you can login with the following credentials after you have activated your account by pressing the url below.

				------------------------
				Username: ' . $email . '
				Password: ' . $password1 . '
				------------------------

				Please click this link to activate your account:
				http://'. $url . '?email=' . $email . '&hash=' . $hash . '

				';
                $headers = "MIME-Version: 1.0" . "\r\n";
                $headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";
				$headers .= 'From:noreply@camagru.com' . "\r\n";
				mail($to, $subject, $message, $headers);
				echo sleep(5) . "<script>alert('Success! We sent an email to $email Please click on the confirmation link in the email to create your account.'); location.href='login.php' </script>";

			} catch (Exception $e) {
				echo "<script>alert('Error: $e');</script>";
				return $e;
			}
		}

		public function exists($id, $code)
		{
			try {
				require 'config/conn.php';
				if (!empty($_GET['email']) && !empty($_GET['hash'])) {
					$id = $_GET['email'];
					$code = $_GET['hash'];
					$y = 1;
					$n = 0;
					global $con;

					$stmt = $con->prepare("SELECT email, Token, Verify FROM users WHERE email=:email AND Token=:Token LIMIT 1");
					$stmt->execute(['email' => $id, 'Token' => $code]);
					$row = $stmt->fetch(PDO::FETCH_ASSOC);
					if ($stmt->rowCount() > 0) {

                            if ($row['Verify'] == $n) {
                                $stmt = $con->prepare("UPDATE users SET Verify=:Verify WHERE email=:email");
                                $stmt->bindparam(":Verify", $y);
                                $stmt->bindparam(":email", $id);
                                $stmt->execute();
                            $msg = 'DONE: Congrats !  Your Account is Now Activated';

                            echo "<script>alert('DONE! Congrats !  Your Account is Now Activated'); location.href='login.php' </script>";
                            return $msg;

                        } else if ($row['Verify'] == $y) {

                            echo "<script>alert('Ooops !  looks like your account is already Active - please Login'); location.href='login.php' </script>";
                            $msg = 'DONE: Ooops !  looks like your account is already Active : please Login';
                            return $msg;
                       } else
                            echo "<script>alert('Ooops !  Something went wrong please try again'); location.href='register.php?email=$id&hash=$code' </script>";

					} else {
						echo "<script>alert(' Sorry! No Account Found : You can Signup'); location.href='register.php' </script>";
					}
				}
			}
			catch (PDOException $ex){
                echo $ex; return; }
		}

		public function is_logged_in()
		{
			if (isset($_SESSION['id'])) {
				return true;
			}
		}
	}
?>