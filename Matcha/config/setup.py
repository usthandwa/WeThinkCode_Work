#!/usr/bin/python
from config import db


def setup():
    db_name = db.get_db()
    # print('Sorry Database already exists')
    try:
        db.query('CREATE DATABASE if not exists {0};'.format(db_name))
    except Exception as e:
        print('Sorry Database already exists')
    # print('Sorry Database already exists')
    try:
        db.query("""CREATE TABLE if not exists User (
        userid INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
        firstname VARCHAR(230) NOT NULL,
        lastname VARCHAR(230) NOT NULL,
        username VARCHAR(130) NOT NULL UNIQUE,
        email VARCHAR(150) NOT NULL,
        pword VARCHAR(300) NOT NULL,
        location VARCHAR(300),
        sex VARCHAR(130),
        age INT(6) UNSIGNED,
        description text,
        interests text,
        Token VARCHAR(250) NOT NULL DEFAULT '0',
        Verify VARCHAR (250) NOT NULL DEFAULT '0',
        notif VARCHAR (250) NOT NULL DEFAULT '0',
        reg_date TIMESTAMP
        ) ENGINE=InnoDB DEFAULT CHARSET=latin1;
        
        CREATE TABLE IF NOT EXISTS user_interest (
        `uid` INT UNSIGNED NOT NULL REFERENCES User(userid),
        `interest_id` INT UNSIGNED
        ) ENGINE=InnoDB DEFAULT CHARSET=latin1;
        
        CREATE TABLE IF NOT EXISTS fame_rating (
        fame_id INT(9) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
		username VARCHAR(50) NOT NULL,
		rating INT(9) NOT NULL
		) ENGINE=InnoDB DEFAULT CHARSET=latin1;
    
        CREATE TABLE IF NOT EXISTS interests (
        `interest_id` INT(11) UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
        `interest` VARCHAR(32) NOT NULL
        ) ENGINE=InnoDB DEFAULT CHARSET=latin1;
    
        CREATE TABLE IF NOT EXISTS user_img (
        `img_id` INT(11) UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
        `uid` INT UNSIGNED NOT NULL REFERENCES User(userid),
        `img_path` VARCHAR(150) NOT NULL,
        `img_name` VARCHAR(150) NOT NULL,
        `active` bool NOT NULL
        ) ENGINE=InnoDB DEFAULT CHARSET=latin1;
    
        CREATE TABLE IF NOT EXISTS likes (
        `uid` INT UNSIGNED NOT NULL REFERENCES User(userid),
        `friend_id` INT UNSIGNED NOT NULL
        ) ENGINE=InnoDB DEFAULT CHARSET=latin1;
    
        CREATE TABLE IF NOT EXISTS views (
        `uid` INT UNSIGNED NOT NULL REFERENCES User(userid),
        `friend_id` INT UNSIGNED NOT NULL
        ) ENGINE=InnoDB DEFAULT CHARSET=latin1;
        
        CREATE TABLE IF NOT EXISTS notification (
        `uid` INT UNSIGNED NOT NULL REFERENCES User(userid),
        `friend_id` INT UNSIGNED NOT NULL,
        `message` text NOT NULL
        ) ENGINE=InnoDB DEFAULT CHARSET=latin1;
        
        CREATE TABLE IF NOT EXISTS chat (
        `uid` INT UNSIGNED NOT NULL REFERENCES User(userid),
        `friend_id` INT UNSIGNED NOT NULL,
        `message` text NOT NULL
        ) ENGINE=InnoDB DEFAULT CHARSET=latin1;
    
        CREATE TABLE IF NOT EXISTS blocked (
        `uid` INT UNSIGNED NOT NULL REFERENCES User(userid),
        `blocked_id` INT UNSIGNED NOT NULL
        ) ENGINE=InnoDB DEFAULT CHARSET=latin1;
    
        CREATE TABLE IF NOT EXISTS report (
        `uid` INT UNSIGNED NOT NULL REFERENCES User(userid),
        `reported_id` INT UNSIGNED NOT NULL
        ) ENGINE=InnoDB DEFAULT CHARSET=latin1; """)
    except Exception as e:
        print('TABLE NOT CREATED\n {0}'.format(e))
