from config import db


def get_all():
    res = db.query("SELECT * FROM User ORDER BY username DESC, location ASC, age ASC")
    return res


def getadd():
    import requests
    import json
    import getip
    ip = getip.get()

    send_url = f'http://api.ipstack.com/{ip}?access_key=7cf3582503675544e752924eb3142e79&format=1'
    r = requests.get(send_url)
    j = json.loads(r.text)
    lat = str(j['latitude'])
    lon = str(j['longitude'])
    print(lat + ", " + lon)
    return j['city'] + ", " + j["country_code"]


class MyFunctions:

    def __init__(self, user, username):
        self.user = user
        self.username = username

    def fame(self):

        try:
            user = self.user
            views = 0
            print(user)
            rating = 0
            stmt = db.query("SELECT * FROM views WHERE friend_id = %s", (user,))

            for row in stmt:
                if row['to_user'] == user:
                    if row['notification'].find("viewed") == 0:
                        views += 1
            if views <= 5:
                rating += 1
            elif 5 < views < 50:
                for i in range(5, 50, 5):
                    rating += i
            if views >= 50:
                rating = 10
            else:
                rating = 0
            db.query("UPDATE fame_rating SET rating = %s WHERE username = %s", (rating, user,))
        except Exception as e:
            print(e)

    def match(self):

        try:
            user1 = str(self.username)
            user2 = str(self.user)
            count = 0
            stmt = db.query("SELECT * FROM likes")

            for row in stmt:
                if row['uid'] == user1 and row['friend_id'] == user2:
                    if row['friend_id'] == user2 and row['uid'] == user1:
                        count += 2
                if count == 2:
                    pair = user1 + ' ' + user2
                    db.query("INSERT INTO matches (pair) VALUES (%s)", (pair,))
                    print(pair + "\n")
                    return True
                else:
                    pair = user1 + ' ' + user2
                    db.query("DELETE FROM matches WHERE pair = %s", (pair,))
                    print(pair + "__2")
                    return False
        except Exception as e:
            print(e)

    def check_notification(self):

        try:
            username = self.username
            notif = 0

            sql = db.query("SELECT * FROM notifications WHERE to_user = %s", (username,))
            for row in sql:
                if row['seen'] == "no":
                    notif += 1
                if notif:
                    return notif
                else:
                    return False
        except Exception as e:
            print(e)

    def read_notifications(self):

        try:
            username = self.username
            db.query("UPDATE notifications SET seen = 'yes' WHERE to_user = %s", (username,))
        except Exception as e:
            print(e)

    def is_blocked(self, blocker, uid):

        try:
            sql = db.query("SELECT * FROM block WHERE blocked = %s", (uid,))
            blocked = 0
            for row in sql:
                if row['blocker'] == blocker:
                    blocked = 1
                if blocked:
                    return True
                else:
                    return False
        except Exception as e:
            print(e)

    def remove_user(self):

        try:
            username = self.username
            user = self.user

            pair = username + ' ' + user
            db.query("DELETE FROM matches WHERE pair = %s", (pair,))

            pair = user + ' ' + username
            db.query("DELETE FROM matches WHERE pair = %s", (pair,))
            db.query("DELETE FROM likes WHERE liker = %s AND liked = %s", (username, user,))
        except Exception as e:
            print(e)

    def suggest_user(self, SESSION):

        try:
            user = self.user
            username = SESSION['username']
            sex_pref = SESSION['sex_pref']
            location = SESSION['location']
            fame = SESSION['fame']
            gender = SESSION['gender']
            sql = db.query(
                "SELECT * FROM users LEFT JOIN fame_rating ON users.username = fame_rating.username WHERE reg_verify = 1")

            for row in sql:
                if user == row['username']:
                    if sex_pref == row['gender'] and row['sexual_pref'] == gender or row['sexual_pref'] == "both":
                        if fame == row['rating'] or row['rating'] > fame:
                            if location == row['user_location']:
                                return True
                    elif sex_pref == "both":
                        if row['sexual_pref'] == gender or row['sexual_pref'] == "both":
                            if fame == row['rating'] or row['rating'] > fame:
                                if location == row['user_location']:
                                    return True
                return False
        except Exception as e:
            print(e)

    def login_status(self):

        try:
            sql = db.query("select verify from user WHERE username = %s"(self.username, ))
            for row in sql:
                if row['Verify'] == '2':
                    return True
                else:
                    return False
        except Exception as e:
            print(e)

    def report(self):

        try:
            db.query("INSERT INTO report (uid, reported_id) VALUES (%s, %s)", (self.user, self.username))
        except Exception as e:
            print(e)

    def block(self):

        try:
            print("user" + str(self.user) + "blocked!!!")
            db.query("INSERT INTO blocked (uid, blocked_id) VALUES (%s, %s)", (self.user, self.username))
        except Exception as e:
            print(e)

    def like(self):

        try:
            print("user" + str(self.user) + "liked!!!")
            db.query("INSERT INTO likes (uid, friend_id) VALUES (%s, %s)", (self.user, self.username))
        except Exception as e:
            print(e)


def rsearch(name, age, fame, location, interest, preference):
    if name:
        sql = f"SELECT * FROM fame_rating LEFT JOIN user ON fame_rating.username = user.username LEFT JOIN interests ON fame_rating.username = user.username WHERE user.username LIKE '%{name}%' AND verify = 1";
        if age:
            sql += f" AND age LIKE '%{age}%'"
        if fame:
            sql += f" AND rating LIKE '%{fame}%'"
        if location:
            sql += f" AND location LIKE '%{location}%'"
        if interest:
            sql += f" AND interests LIKE '%{interest}%'"
        try:
            stmt = db.query(sql)
            print(stmt)
            return stmt
        except Exception as e:
            print("Tiny mistake {} here!%", e)

    elif fame:
        sql = f"SELECT * FROM fame_rating LEFT JOIN user ON fame_rating.username = user.username LEFT JOIN interests ON fame_rating.username = interests.username WHERE rating LIKE '%{fame}%' AND verify = 1";
        if age:
            sql += f" AND age LIKE '%{age}%'"
        if name:
            sql += f" AND user.username LIKE '%{name}%'"
        if location:
            sql += f" AND location LIKE '%{location}%'"
        if interest:
            sql += f" AND interests LIKE '%{interest}%'"
        try:
            stmt = db.query(sql)
            print(stmt)
            return stmt
        except Exception as e:
            print("Tiny mistake %", e)
    elif interest:
        sql = f"SELECT * FROM fame_rating LEFT JOIN user ON fame_rating.username = user.username LEFT JOIN interests ON fame_rating.username = interests.username WHERE interests LIKE '%{interest}%' AND verify = 1 or 2";
        if age:
            sql += f"AND age LIKE '%{age}%'"
        if name:
            sql += f" AND username LIKE '%{name}%'"
        if location:
            sql += f"""AND location LIKE '%{location}%'"""
        if interest:
            sql += f""" AND interests LIKE '%{interest}%'"""
        try:
            stmt = db.query(sql)
            print(stmt)
            return stmt
        except Exception as e:
            print("Tiny mistake %", e)
