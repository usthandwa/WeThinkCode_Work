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
        discription text,
        interests text,
        Token VARCHAR(250) NOT NULL DEFAULT '0',
        Verify VARCHAR (250) NOT NULL DEFAULT '0',
        notif VARCHAR (250) NOT NULL DEFAULT '0',
        reg_date TIMESTAMP
        )""")
    except Exception as e:
        print('TABLE NOT CREATED\n {0}'.format(e))
    # print('Sorry Database already exists')
    try:
        db.query("""CREATE TABLE if not exists Image (
        imageid INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
        userid INT(6) UNSIGNED,
        picname VARCHAR(30) UNIQUE,
        piclocation VARCHAR(50) NOT NULL,
        likes int(11) UNSIGNED NOT NULL DEFAULT '0',
        mod_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP 
        )""")
    except Exception as e:
        print('TABLE NOT CREATED\n {0}'.format(e))
    # print('Sorry Database already exists')
    try:
        db.query("""CREATE TABLE if not exists matching (
        _id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
        likeid INT(6) UNSIGNED,
        likerid INT(6) UNSIGNED,
        _match VARCHAR(250) NOT NULL DEFAULT 'Y',
        _date TIMESTAMP
        )""")
    except Exception as e:
        print('TABLE NOT CREATED\n {0}'.format(e))
    # print('Sorry Database already exists')
    try:
        db.query("""CREATE TABLE if not exists Chat (
        id int(11) UNSIGNED NOT NULL,
        user text CHARACTER SET latin1 COLLATE latin1_bin NOT NULL,
        comment text NOT NULL,
        chat_id int(11) UNSIGNED NOT NULL,
        date_posted datetime NOT NULL
        )""")
    except Exception as e:
        print('TABLE NOT CREATED\n {0}'.format(e))