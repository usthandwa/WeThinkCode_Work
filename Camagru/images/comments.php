<?php
session_start();
require_once "../config/conn.php";
//header( "Content-type: application/json" );
global $con;
try {
    if (isset($_GET['action'])) {
        if ($_GET['action'] == "like") {
            if (isset($_SESSION['id'])) {
                $image_id = $_GET['id'];
                $user = $_SESSION['fname'];
                $like = 1;
                /* Avoiding more than 1 like from the same user on one image */
                $liked = $con->query("SELECT id FROM post_likes WHERE user= '" . htmlentities($user) . "' AND image_id = '".htmlentities($image_id)."'");
                $liked = $liked->fetch();
                if (!$liked) {
                    $return = $con->prepare("INSERT INTO post_likes (user, likesNo, image_id) VALUES (:user, :likesNo, :image_id)")->execute(array(':user' => $user, ':likesNo' => $like, ':image_id' => $image_id));
                }
            }
            echo "<script>location.href='Gallery.php'; </script>";
        } else if ($_GET['action'] == "comment") {
            $image_id = $_GET['id'];
            $commenter = $_SESSION['fname'];
            if (isset($_SESSION['id'])) {

                $user_posted = $con->prepare("SELECT count(2), userid FROM images WHERE imageid=:image_id");
                $user_posted->execute(['image_id' => $image_id])[0]['userid'];
                $user_posted = $user_posted->fetch(PDO::FETCH_COLUMN);

                $recipient = $con->prepare("SELECT email FROM users WHERE userid=:userid");
                $recipient->execute([':userid' => $user_posted])[0]['email'];
                $recipient = $recipient->fetch(PDO::FETCH_COLUMN);

                $message = htmlspecialchars($_GET['message']);
                $savior = $con->prepare("SELECT comment FROM comments WHERE user=:userid AND image_id=:image_id");
                $savior->execute([':userid' => $commenter, ':image_id' => $image_id]);
                $savior = $savior->fetchAll(PDO::FETCH_COLUMN);
                /* Fixing the multiple comment problem */
                $index = 0;

                foreach ($savior as $value) {
                    if (strcmp($value, $message) == 0)
                        die("<script>location.href='Gallery.php'; </script>");
                    $index++;
                }
                if (strlen($message) > 1) {
                    $stmt = $con->prepare("INSERT INTO comments (user, comment, image_id, date_posted) VALUES (:user, :comment, :image_id, NOW())")->execute(array(':user' => $commenter, ':comment' => $message, ':image_id' => $image_id));
                    echo json_encode($stmt);
                }

                /* According to email notif prefs */
                $pic_owner = $con->query("SELECT firstname FROM users WHERE userid= '" . htmlentities($user_posted) . "'")->fetch()['firstname'];
                $notif_db = $con->query("SELECT notif FROM users WHERE userid= '" . htmlentities($user_posted) . "'")->fetch()[0]['notif'];
                if (!$notif_db) {
                    $htmlStr = "";
                    $htmlStr .= "Hi " . $pic_owner . "<br /><br />";
                    $htmlStr .= $commenter . " commented on your photo and said:<br />" . $message . "<br /><br />";
                    $htmlStr .= "Kind regards, <br />";
                    $htmlStr .= "Camargu";
                    $name = "Camagru";
                    $email_sender = "noreply@camagru.co.za";
                    $subject = "Camagru Notification";

                    $headers = "MIME-Version: 1.0" . "\r\n";
                    $headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";
                    $headers .= "From: {$name} <{$email_sender}> \n";
                    mail($recipient, $subject, $htmlStr, $headers);
                }
                echo "<script>location.href='Gallery.php'; </script>";
            }
        }
    }
}catch (Exception $d) {
    $err .= " " . htmlentities($d->getMessage()) ."\"". " ";
    $err .= "\"" . htmlspecialchars($d->getTraceAsString()) ."\"". " ";
    echo '<script>alert("Oops!! looks like you\'ve managed to break something: ' .$err.'" ); </script>';
}
