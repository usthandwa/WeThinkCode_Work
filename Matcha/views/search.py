from config import db


def search(name, age, fame, location, interest):
    if name:
        sql = f"""SELECT * FROM fame_rating LEFT JOIN users ON fame_rating.username = users.username LEFT JOIN interests ON fame_rating.username = interests.username WHERE rating LIKE '%{name}%' AND reg_verify = 1""";
        if age:
            sql += f"""AND age LIKE '%{age}%'"""
        if fame:
            sql += f""" AND name LIKE '%{fame}%'"""
        if location:
            sql += f"""AND user_location LIKE '%{location}%'"""
        if interest:
            sql += f" AND interest LIKE '%{interest}%'"
        try:
            db.query(sql)
        except Exception as e:
            print("Tiny mistake %", e)

    elif fame:
        sql = f"""SELECT * FROM fame_rating LEFT JOIN users ON fame_rating.username = users.username LEFT JOIN interests ON fame_rating.username = interests.username WHERE rating LIKE '%{fame}%' AND reg_verify = 1""";
        if age:
            sql += f"""AND age LIKE '%{age}%'"""
        if name:
            sql += f""" AND name LIKE '%{name}%'"""
        if location:
            sql += f"""AND user_location LIKE '%{location}%'"""
        if interest:
            sql += f""" AND interest LIKE '%{interest}%'"""
        try:
            db.query(sql)
        except Exception as e:
            print("Tiny mistake %", e)
    elif interest:
        sql = f"""SELECT * FROM fame_rating LEFT JOIN users ON fame_rating.username = users.username LEFT JOIN interests ON fame_rating.username = interests.username WHERE rating LIKE '%{interest}%' AND reg_verify = 1""";
        if age:
            sql += f"""AND age LIKE '%{age}%'"""
        if name:
            sql += f""" AND name LIKE '%{name}%'"""
        if location:
            sql += f"""AND user_location LIKE '%{location}%'"""
        if interest:
            sql += f""" AND interest LIKE '%{interest}%'"""
        try:
            db.query(sql)
        except Exception as e:
            print("Tiny mistake %", e)
