import html
from flask import request
from config import db, config
from views.sendmail import sendmail
from config.config import get_hash


def exists(email, code):
    try:
        y = 1
        n = 0

        stmt = db.query("SELECT email, Token, Verify FROM User WHERE email=%s AND Token=%s LIMIT 1", (email, code,));
        if stmt:
            for row in stmt:
                print(row['Verify'])
                if row['Verify'] == '0':
                    db.query("UPDATE user SET Verify=%s WHERE email=%s", (y, email,))
                    msg = 'DONE: Congrats !  Your Account is Now Activated'
                    return msg
                elif row['Verify'] == '1':
                    msg = 'DONE: Ooops !  looks like your account is already Active: please Login'
                    return msg
                else:
                    return 'Ooops !  Something went wrong please try again'
        else:
            return ' Sorry! No Account Found : You can Signup'
    except Exception as e:
        print(e)
        return e


def verify(username, email, code):
    try:
        email = html.escape(email)
        url = request.url
        if email and code:
            message = f"""Hello , {username}<br><br>

            Thank you for joining our site, let's find your match!<br><br>
            http://{url}?email={email}&code={code}' << click here to activate account<br><br>

            Thank you :)<br> """
            subject = "Matcha | Account Verification"
            sendmail(email, email, subject, message)
            return f"Success! We sent an email to {email}, Please follow link to verify your account, before you log in..."
        else:
            return "'Sorry! No Account Found : You can Signup"
    except Exception as e:
        echo = "Error: %s" % e
        print(echo)
        return echo


def reset(email):
    try:
        email = html.escape(email)
        url = request.base_url
        stmt = db.query("""SELECT userid FROM user WHERE email=%s LIMIT 1""", (email,))
        for row in stmt:
            if stmt:
                from config.config import get_hash
                uid = row['userid']
                code = config.get_hash(email)

                db.query("""UPDATE user SET Token= %s WHERE email= %s""", (code, email,))
                message = f"""Hello , {email}<br>
                
                We got requested to reset your password, <br>if you do this then just click 
                the following link to reset your password, if not just ignore this email,<br>
                
                Click following link to reset rour Password<br>
                http://{url}?id={uid}&code={code}' << click here to reset your password<br><br>
                
                Thank you :)<br>"""
                subject = "Matcha | Password Reset"
                sendmail(email, email, subject, message)
                return "Success! We sent an email to $email Please click on the password reset link in the email to generate new password."
            else:
                return "Sorry! No Account Found : You can Signup"
    except Exception as e:
        echo = "Error: %s" % e
        print(echo)
        return echo


def change_pw(passw, cpass, *args):
    if args:
        uid = get_hash(args[1])
        code = args[2]
        stmt = db.query("SELECT * FROM user WHERE userid=%s AND Token=%s", (uid, code,))
        if not stmt:
            return "Error: was not able to verify user"
    if cpass != passw:
        return "Error: please confirm your password"
    else:
        code = 1;
        passwd = config.get_hash(cpass)
        db.query("UPDATE user SET pword=%s, Token=%s WHERE userid=%s", (passwd, code, args[1],))
        return "Password Changed"
