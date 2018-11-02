<?php
	session_start();

	require_once  "config/conn.php";
	require "src/verify.php";

    $class = new camagru();
    if ($class->is_logged_in())
    {
	    echo "<script>alert('Welcome back'); location.href='images/Gallery.php' </script>";
    }
	if (!empty($_SESSION['id'])) {
		$id = $_SESSION['id'];
		$photos = $con->query("SELECT * FROM post_likes")->FetchAll();
		$comments = $con->query("SELECT * FROM comments ORDER BY date_posted DESC")->FetchAll();

		if ($_POST['like']) {
			$image_id = $_POST['like'];
			echo "<script>location.href='Gallery.php?action=like&id=$image_id'</script>";
		} elseif ($_POST['comment']) {
			$image_id = $_POST['comment'];
			echo "<script>location.href='Gallery.php?action=comment&id=$image_id&message=$image_id'</script>";
		}
	}
?>
<!DOCTYPE HTML>
<html class="page">
<head>
    <meta http-equiv="Content-Type"
          content="width=device-width, initial scale=1; text/html; charset=utf-8"/>
    <title>CAMAGRU : Gallery</title>
    <link rel="stylesheet" href="style/style.css" type="text/css"/>
</head>
<body>
<ul class="">
    <!-- <li><a href="images/camera.php">Home</a></li>
    <li><a href="profile.php">Profile</a></li> -->
    <li><a class="active" href="#">Gallery</a></li>
    <li style="float: right"><a href="src/login.php">Login</a></li>
	<li style="float: right"><a href="src/register.php">SignUp</a></li>
</ul>
<div class="page__demo">
    <h2>| CAMAGRU: Gallery |</h2> <br>
    <div class="row page__container">
    <div class="column middle">
        <div class="container_pic center">
            <table>
                    <?php
				try {
	                    $aItems = $con->prepare('SELECT * FROM images'); // get photos info
	                    $aItems->execute();
	                    $tot = $aItems->RowCount();
	                    $i = 0;
	                    $limit = 5;
	                    $total_pages = ceil($tot / $limit);

	                    if (!isset($_GET['page'])) {
		                    $page = 1;
	                    } else {
		                    $page = $_GET['page'];
	                    }
	                    $starting_limit = ($page - 1) * $limit;

	                    $aItems = $con->prepare("SELECT * FROM images ORDER BY mod_date DESC LIMIT $starting_limit, $limit"); // get photos info
	                    $aItems->execute();
	                    while ($row = $aItems->fetch(PDO::FETCH_ASSOC)) {
	                    $image = $row['picname'];
	                    $imageid = $row['imageid'];
	                    $i++;

	                    //<-- Comments section -->?>

                <tr valign="middle !important">

                        <td valign="top"><img class="photo_wrp"
                                            src="images/uploads/<?php echo $image ?>"
                                            >
                    <form class="middle" method="post" enctype="multipart/form-data">
                        <span>
                            <label class="field field_type3">
                                 <?php
	                                 /* Retreive the number of likes */
	                                 $total_post_likes = 0;
	                                 foreach($photos as $like) {
		                                 if ($imageid == $like['image_id']) {
			                                 $total_post_likes += $like['likesNo']; /* Accumulate likes */
		                                 }
	                                 }
	                                 echo "post_likes";
	                                 echo ": ";
	                                 echo "<b>".$total_post_likes."</b>";
	                                 //echo "</div>";
	                                 $total_post_likes = 0;
                                 ?>
                                <span class="field__label-wrap"> </span>
                            </label>
                            <?php
                            foreach($comments as $comment) {
	                            if ($imageid == $comment['image_id']) { ?>
		                            <?php echo "<span><br />" . $comment['user'] . "<b></span>" . " <b />:<b /> " . "<span>" . $comment['comment'] . "<b /></span>";
	                            }
                            }
	                        ?>
                        </span>
                    </form>
                    </td>

                </tr>
		                    <?php
	                    }
                    ?>
            </table>
    </div>
    </div>
    </div>
</div>
<br>
    <div class="footer center">
<!--        <div id="overlay"><div><img src="loading.gif" width="60%" height="64px"/></div></div>-->
        <div class="pagination">
            <a href="<?php echo "?page=1";?>">&laquo;</a>
            <?php for ($page = 1; $page <= $total_pages; $page++):?>
              <a class="test" href='<?php echo "?page=$page"; ?>'><?php echo  $page; ?></a>

            <?php endfor;?>
            <a href="<?php echo "?page=$total_pages"; ?>">&raquo;</a>
            <?php
				}catch (PDOException $e) {
				$e = $e->getTraceAsString();
				echo "<script>alert('ERROR : $e'); location.href='#' </script>";
			}

			?>

        </div>
    </div>

</body>
</html>