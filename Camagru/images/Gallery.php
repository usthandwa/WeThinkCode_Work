<?php
session_start();
ob_start();
require_once "../src/verify.php";
require_once('../config/conn.php'); // include service classes to work with database and comments
$class = new camagru();
if (!$class->is_logged_in()) {
    echo "<script>location.href='../index.php' </script>";
}
if (!empty($_SESSION['id'])) {
    $id = $_SESSION['id'];
    $photos = $con->query("SELECT * FROM post_likes")->FetchAll();
    $comments = $con->query("SELECT * FROM comments ORDER BY date_posted DESC")->FetchAll();
}
if (isset($_POST['send'])) {
    echo "<p>" . $page = $_POST['send'] . "</p>";
    get_more();
} else {
    $page = !isset($_GET['page']) ? 1 : $_GET['page'];
    ?>
    <!DOCTYPE HTML>
    <html class="page">

    <head>
        <link rel="stylesheet" href="../style/style.css" type="text/css"/>
        <meta http-equiv="Content-Type" content="width=device-width, initial scale=1; text/html; charset=utf-8"/>
        <title>CAMAGRU : Gallery</title>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    </head>

    <body>
    <ul class="">
        <li><a href="camera.php">Home</a></li>
        <li><a href="../src/profile.php">Profile</a></li>
        <li><a class="active" href="Gallery.php">Gallery</a></li>
        <li style="float: right"><a href="../src/logout.php">LogOut</a></li>
    </ul>
    <div >
        <h2 class="header">| CAMAGRU: Gallery |</h2>
        <hr>
    </div>
    <div class="page__demo row demo-wrapper">
        <div class="column side"></div>
        <div class="column middle">
            <div class="center" id="content"  >
                    <?php
                    try {
                    get_more();
                    ?>
            </div>
        </div>
        <br>
<!--        <div class="side right"></div>-->
    </div>
    <div class="footer center">

        <!--        <div id="overlay"><div><img src="loading.gif" width="60%" height="64px"/></div></div>-->
        <div class="pagination">
            <a href="<?php echo " ?page=1 "; ?>">&laquo;</a>
            <?php
            global $total_pages;
            for ($page = 1; $page <= $total_pages; $page++): ?>
                <a class="test" href='<?php echo "?page=$page"; ?>'>
                    <?php echo $page; ?>
                </a>

            <?php endfor; ?>
            <a href="<?php echo " ?page=$total_pages "; ?>">&raquo;</a>
            <?php
            } catch (PDOException $e) {
                $e = $e->getTraceAsString();
                echo "<script>alert('ERROR : $e'); location.href='Gallery.php'; </script>";
            }
            ?>

        </div>
    <div class="footer">
        <hr/>
        <strong>@szama #CAMAGRU</strong>
    </div>
    </div>
    <script type="text/javascript"></script>
    <script> var total = <?=$total_pages?> </script>
    <script src="js/comment_.js" type="text/javascript"></script>
    <script src="js/scroll.js" type="text/javascript"></script>
    </body>

    </html>

    <?PHP
}

function get_more()
{
    global $con;
    GLOBAL $photos;
    global $comments;
    global $total_pages;
    global $page;

    echo "<table>";

    $tot = $con->query("SELECT COUNT(*) FROM images")->fetchColumn();
    $i = 0;
    $limit = 5;
    $total_pages = ceil($tot / $limit);
    $starting_limit = ($page - 1) * $limit;
    $aItems = $con->prepare("SELECT * FROM images ORDER BY picname DESC LIMIT $starting_limit, $limit"); // get photos info
    $aItems->execute();
    while ($row = $aItems->fetch(PDO::FETCH_ASSOC)) {
        $image = $row['picname'];
        $imageid = $row['imageid'];
        $i++;

        //<-- Comments section -->?>
        <tr valign="middle !important">
            <td valign="top" class='photo'><img class="photo_wrp" src="uploads/<?php echo $image; ?>">
                <form class="middle" method="post" enctype="multipart/form-data">
                        <span>
                            <label class="field field_type3">
                                <?php
                                /* Retreive the number of likes */
                                $total_post_likes = 0;
                                foreach ($photos as $like) {
                                    if ($imageid == $like['image_id']) {
                                        $total_post_likes += $like['likesNo']; /* Accumulate likes */
                                    }
                                }
                                echo "post_likes";
                                echo ": ";
                                echo "<b>" . $total_post_likes . "</b>";
                                //echo "</div>";
                                $total_post_likes = 0;
                                ?>
                                <br>
                                <textarea class="button field__input"
                                          placeholder="Enter a comment"
                                          style="padding-top: 2%;"
                                          name="<?php echo $imageid; ?>"
                                          id="message"></textarea>
                            </label>
                            <div class="grid">
                            <button type="submit" id="like" class="button"

                                    style="width: 100%; height: 100%"
                                    value="<?php echo $imageid; ?>" id="like"
                                    onclick="return likeImage(this)">Like
                            </button>
                            <button id="comment" name="comment" type="submit" class="button"
style="width: 100%; height: 100%"
                                    value="<?php echo $imageid; ?>"
                                    onclick="return submitComment(this)">Comment
                            </button>

                            </div>
                            <br>
                            <div class="comments">

                            <?php
                            foreach ($comments as $comment) {
                                if ($imageid == $comment['image_id']) {
                                    echo "<br/> <p> <span style='width: 30%'> <br/>" . $comment['user'] . "<b></span> <b/> : <b/> <span style='width: 20%'>" . $comment['comment'] . "<b/> </span> <p>";
                                }
                            }
                            ?>
                            </div>
                        </span>
                </form>
            </td>
        </tr>
        <?php
    }
    echo "</table>";
}

?>
