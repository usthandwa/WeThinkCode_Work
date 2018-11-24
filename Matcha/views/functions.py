


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


def fame__():
    from config import db
    from flask import session
    views = 0
    user = "secret" #session.get('logged_in')
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
    print("up to here")
    db.query("UPDATE fame_rating SET rating = %s WHERE username = %s", (rating, user,))
