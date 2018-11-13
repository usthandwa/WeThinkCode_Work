import db


def get_all():
    res = db.query("SELECT * FROM User ORDER BY username DESC, location ASC, age ASC")
    return res
