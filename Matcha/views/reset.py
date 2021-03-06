import base64
import os, html

from config import db, config
from views.sendmail import sendmail


def reset(email):
    try:
        email = html.escape(email)
        url = os.environ['HTTP_HOST'] + os.environ['REQUEST_URI']
        stmt = db.query("""SELECT userid FROM users WHERE email=%s LIMIT 1""", (email,))
        if stmt:
            uid = base64(stmt['userid'])
            code = config.get_hash(uid)
            from config.config import get_hash

            db.query("""UPDATE users SET Token= %s WHERE email= %s""", (code, email,))
            message = f"""Hello , {email}
            
            We got requested to reset your password, if you do this then just click 
            the following link to reset your password, if not just ignore this email,
            
            Click following link to reset rour Password
            http://{url}?id={uid}&code={code}' << click here to reset your password
            
            Thank you :) """
            subject = "Matcha | Password Reset"
            sendmail(email, email, subject, message)
            return "<script>alert('Success! We sent an email to $email Please click on the password reset link in the email to generate new password.'); < / script > "
        else:
            return "<script>alert('Sorry! No Account Found : You can Signup'); location.href='register.php' </script>"
    except Exception as e:
        echo = "<script>alert('Error: %s'); </script>" % e
        print(echo)
        return echo


def change_pw(passw, cpass, *args):
    if args:
        uid = base64(args[1])
        code = args[2]
        stmt = db.query("SELECT * FROM users WHERE userid=%s AND Token=%s", (uid, code,))
        if not stmt:
            return "Error: was not able to verify user"
    if cpass != passw:
        return "Error: please confirm your password"
    else:
        code = 1;
        passwd = config.get_hash(cpass)
        db.query("UPDATE users SET pword=%s, Token=%s WHERE userid=%s", (passwd, code, args[1],))
        return "Password Changed"
