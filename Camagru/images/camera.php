<?PHP
session_start();
require_once "../config/conn.php";
require "../src/verify.php";
$class = new camagru();

if (!$class->is_logged_in()) {
    echo "<script>alert('Oops!! looks like you\'re not logged in! click ok to login'); location.href='../src/login.php' </script>";
} else
    $id = $_SESSION['id'];
if (isset($_POST['filter'])) {
    $filepath0 = "overlays/" . $_POST['filter'];
    $dest = imagecreatefrompng($filepath0);
    imagepng($dest, "temp/image1.png");
} else {
    if (file_exists("temp/image1.png"))
        unlink("temp/image1.png");
    $filepath0 = "overlays/clear.png";
}
$type0 = pathinfo($filepath0, PATHINFO_EXTENSION);
$data0 = file_get_contents($filepath0);
$image0 = 'data:image/png;' . $type0 . ';base64,' . base64_encode($data0);
?>

<!DOCTYPE HTML>
<html class="page">

<head>
    <meta http-equiv="Content-Type" content="width=device-width, initial scale=1; text/html; charset=utf-8"/>
    <title> CAMAGRU: Camera </title>
    <link rel="stylesheet" href="../style/style.css" type="text/css"/>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
</head>

<body>
<ul class="navbar">
    <li><a class="active" href="camera.php">Home</a></li>
    <li><a href="../src/profile.php">Profile</a></li>
    <li><a href="Gallery.php">Gallery</a></li>
    <li style="float: right"><a href="../src/logout.php">LogOut</a></li>
</ul>
<div>
    <h2 class="header"> CAMAGRU: Work Area </h2>
    <hr>
</div>
<div class="page__demo row demo-wrapper">
    <div class="column side">
        <div class="cc-selector">
            <br><label class="field__label" style="text-align: center; text-underline-mode: auto; color: #3e68e">
                Overlays </label><br>
            <form method="POST" enctype="multipart/form-data" action="#">
                <input id="crown" onchange='this.form.submit();' type="radio" name="filter" value="crown.png"
                       alt="Crown"/>
                <label class="drinkcard-cc crown" for="crown"></label><br>

                <input id="like_boss" onchange='this.form.submit();' type="radio" name="filter" value="likeboss.png"
                       alt="Like Boss"/>
                <label class="drinkcard-cc like_boss" for="like_boss"></label><br>

                <input id="dogface" type="radio" onchange='this.form.submit();' name="filter" value="dogface.png"
                       alt="Dog Ears"/>
                <label class="drinkcard-cc dogface" for="dogface"></label><br>

                <input id="ears" type="radio" onchange='this.form.submit();' name="filter" value="ears.png"
                       alt="Hearts"/>
                <label class="drinkcard-cc ears" for="ears"></label><br>

                <input id="idea" type="radio" onchange="this.form.submit();" name="filter" value="idea.png"
                       alt="idea/lightbulb"/>
                <label class="drinkcard-cc idea" for="idea"></label><br>
            </form>
        </div>
    </div>
    <div class="column middle grid">
        <div class="container">
            <img id="superimg" src="<?php echo $image0 ?>" width="500" height="375">
            <video id="video" width="500" height="375" autoplay src=""></video>
            <?PHP if (isset($_POST['filter'])) {

                echo '<button id="snap" class="overlay" name="snap">Snap Photo</button><br>
                        <label class="field__label" style="text-align: center ">Click on video to take picture</label>';
            } else
                echo '<br><label class="field__label" style="text-align: center; text-underline: auto; color: red">Please select overlay to be able to take picture </label>';
            ?>
        </div>
        <div class="container">
            <canvas id="canvas" width="500" height="375" src=""></canvas>
            <input type="hidden" name="display" id="display" value ""/>
            <br>
            <form method="post" enctype="multipart/form-data" action="save_image.php">

                <input type="hidden" name="sub-image" id="sub-image" value ""/>
                <input type="hidden" name="up-image" id="up-image" value ""/>
                <label for="fileToUpload" class="button">Upload image</label>
                <input class="hidden" style="width: 50%" type="file" name="fileToUpload" id="fileToUpload">
                <button id="save" name="save" class="button snap">Save Photo</button>
                <br>
            </form>
        </div>
    </div>
    <div class="column right">
        <form method="post" enctype="multipart/form-data" >
            <?php

            $stmt = $con->prepare("SELECT * FROM images WHERE userid = $id ORDER BY imageid DESC LIMIT 6");
            $stmt->execute(['uid' => $uid]);
            if ($stmt->rowCount()) {
            $result = $stmt->fetchAll();
            $tot = $stmt->rowCount();
            $i = 0;
            //THIS ECHO'S EACH IMAGE THIS USER HAS SAVED, FROM DATABASE ONTO WEB PAGE
            foreach ($result as $row) {
                $image = $row['picname'];
                $tot--; ?>

                <div class="row">
                <div class="cc-selector">
                    <button class="button" type="submit" onclick="return Delete(this.value);" style="width:100%"
                            value="<?php echo $row['imageid'] ?>" name="delete" id="delete"> Delete image</button><br>
                    <img class="photo" name="delete" src="uploads/<?php echo $row['picname'] ?>"
                         style="width:100%" alt="<?php echo $row['picname'] ?>">
                </div>
                </div>
                <?php $i++;
            } ?>
        </form>
    </div>
    <?php

    }
    ?>
</div>
<div class="footer">
    <hr/>
    <strong>@szama #CAMAGRU</strong>
</div>

<script src="js/photo.js"></script>
</body>

</html>
