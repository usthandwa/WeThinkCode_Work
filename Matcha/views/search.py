from config import db


def search(name, age, fame, location, interest):
if name:
    sql = """SELECT * FROM fame_rating LEFT JOIN users ON fame_rating.username = users.username LEFT JOIN interests ON fame_rating.username = interests.username WHERE rating LIKE '%name%' AND reg_verify = 1""";
    if age:
        sql += """AND age LIKE '%age%'"""
    if fame:
        sql += """ AND name LIKE '%fame%'"""
    if location:
        sql += """AND user_location LIKE '%location%'"""
    if interest:
        sql+= """ AND interest LIKE '%interest%'"""
    try:
        db.query(sql)
    except Exception as e:
        print("Tiny mistake %", e)

else if fame:
    sql = """SELECT * FROM fame_rating LEFT JOIN users ON fame_rating.username = users.username LEFT JOIN interests ON fame_rating.username = interests.username WHERE rating LIKE '%$fame%' AND reg_verify = 1""";
    if age:
        sql += """AND age LIKE '%age%'"""
    if name:
        sql += """ AND name LIKE '%name%'"""
    if location:
        sql += """AND user_location LIKE '%location%'"""
    if interest:
        sql+= """ AND interest LIKE '%interest%'"""
    try:
        db.query(sql)
    except Exception as e:
        print("Tiny mistake %", e)

else if interest:
    sql = """SELECT * FROM fame_rating LEFT JOIN users ON fame_rating.username = users.username LEFT JOIN interests ON fame_rating.username = interests.username WHERE rating LIKE '%interest%' AND reg_verify = 1""";
    if age:
        sql += """AND age LIKE '%age%'"""
    if name:
        sql += """ AND name LIKE '%name%'"""
    if location:
        sql += """AND user_location LIKE '%location%'"""
    if interest:
        sql+= """ AND interest LIKE '%interest%'"""
    try:
        db.query(sql)
    except Exception as e:
        print("Tiny mistake %", e)

