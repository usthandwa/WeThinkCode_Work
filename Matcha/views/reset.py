import html
from flask import request, url_for
from config import db, config
from views.sendmail import sendmail
from config.config import get_hash


def exists(email, code):
    try:
        y = 1
        n = 0

        stmt = db.query("SELECT email, Token, Verify FROM User WHERE email=%s AND Token=%s LIMIT 1", (email, code,))
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
            {url}?email={email}&code={code} << click here to activate account<br><br>

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
        url = url_for(".change", _external=True, _method='GET')
        stmt = db.query("SELECT userid FROM user WHERE email=%s LIMIT 1", (email,))
        for row in stmt:
            if stmt:
                from config.config import get_hash
                uid = row['userid']
                code = config.get_hash(email)

                db.query("""UPDATE user SET Token= %s WHERE email= %s""", (code, email,))
                message = f""" <bold>Hello </bold>, {email}<br><br>
                
                We got requested to reset your password, <br>if you do this then just click 
                the following link to reset your password, if not just ignore this email,<br>
                
                {url}?id={uid}&code={code} << click here to reset your password<br><br>
                
                Thank you :)<br>"""
                subject = "Matcha | Password Reset"
                sendmail(email, email, subject, message)
                return f"Success! We sent an email to {email} Please click on the password reset link in the email to generate new password."
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


function
login_status($user){
    require
"../server/pdo.php";
if (session_status() == PHP_SESSION_NONE)
{session_start();}
if (!empty($_SESSION)){
$user = $_SESSION['username'];

$sql = "UPDATE users SET login_status = 'online' WHERE username = :username";
$stmt = $db->prepare($sql);
$stmt->bindParam(':username', $user);
$stmt->execute();
}
}

function
check_propic($user){
    require
"../server/pdo.php";
$sql = "SELECT * FROM propics WHERE username = :user";
$stmt = $db->prepare($sql);
$stmt->bindParam(':user', $user);
$stmt->execute();
$row = $stmt->fetch(PDO::FETCH_ASSOC);
if (!empty($row['propic']))
return true;
return false;

function

$stmt = $db->prepare($sql);
$stmt->bindParam(':username',$username);
$stmt->execute();
}
function

function
remove_user($user){
require
"../server/pdo.php";
if (session_status() == PHP_SESSION_NONE) {session_start();}
$username = $_SESSION['username'];
$pair = $username.
' '.$user;
$sql = "DELETE FROM matches WHERE pair = :pair";
$stmt = $db->prepare($sql);
$stmt->bindParam(":pair", $pair);
$stmt->execute();
$pair = $user.
' '.$username;
$sql = "DELETE FROM matches WHERE pair = :pair";
$stmt = $db->prepare($sql);
$stmt->bindParam(":pair", $pair);
$stmt->execute();
$sql = "DELETE FROM likes WHERE liker = :liker AND liked = :liked";
$stmt = $db->prepare($sql);
$stmt->bindParam(":liker", $username);
$stmt->bindParam(":liked", $user);
$stmt->execute();
echo
"<meta http-equiv='refresh' content='0'>";

}
function
suggest_user($user){
require
"../server/pdo.php";
if (session_status() == PHP_SESSION_NONE) {session_start();}
$username = $_SESSION['username'];
$sex_pref = $_SESSION['sex_pref'];
$location = $_SESSION['location'];
$fame = $_SESSION['fame'];
$gender = $_SESSION['gender'];
$sql = "SELECT * FROM users LEFT JOIN fame_rating ON users.username = fame_rating.username WHERE reg_verify = 1";
$stmt = $db->prepare($sql);
$stmt->execute();
while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
if ($user == $row['username']){
if ($sex_pref == $row['gender'] & & ($row['sexual_pref'] == $gender | | $row['sexual_pref'] == "both")){
if ($fame == $row['rating'] | | $row['rating'] > $fame){
if ($location == $row['user_location'])
return true;
}
}
else if ($sex_pref == "both"){
if ($row['sexual_pref'] == $gender | | $row['sexual_pref'] == "both")
if ($fame == $row['rating'] | | $row['rating'] > $fame){
if ($location == $row['user_location'])
    return true;
}

}
}
return false;
}
}
