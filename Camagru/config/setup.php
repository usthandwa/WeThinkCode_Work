<?php

include "database.php";

try {
	$opt = [
		PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
		PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
		PDO::ATTR_EMULATE_PREPARES   => false,
	];
    $conn = new PDO("mysql:host=$servername;", $username, $password, $opt);
    // set the PDO error mode to exception
    $sql = "CREATE DATABASE IF NOT EXISTS camagru";
    // use exec() because no results are returned
    $conn->exec($sql);
    //echo "Database created successfully<br>";
    $sql = "USE camagru";
    $conn->exec($sql);

    $sql = "CREATE TABLE IF NOT EXISTS users (
		userid INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
		username VARCHAR(130) NOT NULL UNIQUE,
		email VARCHAR(150) NOT NULL,
		pword VARCHAR(300) NOT NULL,
		Token VARCHAR(250) NOT NULL DEFAULT '0',
		Verify VARCHAR (250) NOT NULL DEFAULT '0',
		notif VARCHAR (250) NOT NULL DEFAULT '1',
		reg_date TIMESTAMP
		)";
    $conn->exec($sql);

    $sql = "CREATE TABLE IF NOT EXISTS images (
		imageid INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
		userid INT(6) UNSIGNED,
		picname VARCHAR(30) UNIQUE,
		piclocation VARCHAR(50) NOT NULL,
		likes int(11) UNSIGNED NOT NULL DEFAULT '0',
		mod_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP 
		)";
    $conn->exec($sql);

    $sql = "ALTER TABLE images 
			ADD CONSTRAINT `images_key` 
			FOREIGN KEY (`userid`) 
			REFERENCES `users`(`userid`) 
			ON DELETE SET NULL ON UPDATE CASCADE";
	//$conn->exec($sql);

    $sql = "CREATE TABLE IF NOT EXISTS comments (
	`id` int(11) UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
                user text CHARACTER SET latin1 COLLATE latin1_bin NOT NULL,
                comment text NOT NULL,
                image_id int(11) UNSIGNED NOT NULL,
                date_posted datetime NOT NULL
              ) ENGINE=InnoDB DEFAULT CHARSET=latin1";
	$conn->exec($sql);

	$sql = "CREATE TABLE IF NOT EXISTS post_likes (
				id int(11) UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
                user varchar(32) DEFAULT NULL,
                likesNo int(11) NOT NULL DEFAULT '0',
                image_id int(11) UNSIGNED NOT NULL
              ) ENGINE=InnoDB DEFAULT CHARSET=latin1";
	$conn->exec($sql);

}
catch(PDOException $e)    {
    echo $sql . "\n<br>" . $e->getMessage();
}

//if ($_SESSION['id']) {
//	try {
//		$dir = '../images/uploads';
//		$files = scandir($dir);
//		foreach ($files as $file) {
//			if (fnmatch('*.png', $file)) {
//				$location = "uploads/" . $file;
//				$id = $_SESSION['id'];
//				$query = $conn->prepare("INSERT INTO images (userid, picname, piclocation) VALUES ('$id', '$file', '$location')");
//				$query->execute();
//			}
//		}
//	} catch (PDOException $e) {
//
//	}
//}

//$conn = null;
