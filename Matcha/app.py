import re, os, html

from flask import Flask, render_template, redirect, url_for, request, session, flash
from config.db import query
from config.setup import *
from views.reset import *
from views.functions import *
from views.functions import rsearch
from werkzeug.utils import secure_filename

UPLOAD_FOLDER = "/static/images"
ALLOWED_EXTENSIONS = set(['png', 'jpg', 'jpeg', 'gif'])

app = Flask(__name__)
app.secret_key = "7h1$/H0u$3_b17ch1n\'"
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024
setup()


@app.route('/')
def home():
    if not session.get('logged_in'):
        return login()
    else:
        return browse()


@app.route('/chat')
def chat():
    error = ''
    return render_template('chat.html', error=error, title='chat', logged_in=session.get('logged_in'))


@app.route('/home', methods=['GET', 'POST'])
def browse():
    if not session.get('logged_in'):
        return login()
    else:
        test = MyFunctions(session.get('uid'), '1')
        flash("Logged in successfully.")
        result = get_all()
        test.match()
        test.fame()
        if request.method == 'POST':
            if request.form.get('block'):
                print("to test")
                test.block()
            if request.form.get('report'):
                print("to test report")
                test.report()
            if request.form.get('like'):
                print("to test like")
                test.like()
        return render_template('home.html', title='Home', logged_in=session.get('logged_in'), data=result)


# Route for handling the login page logic
@app.route('/login', methods=['GET', 'POST'])
def login():
    if session.get('logged_in'):
        return browse()
    else:
        error = ""
        if request.method == 'POST':
            username = html.escape(request.form['username'])
            passw = get_hash(request.form['password'])
            res = query("SELECT * FROM User WHERE username = %s AND pword = %s", (username, passw))
            if res:
                for row in res:
                    if row["username"] != username or passw != row["pword"]:
                        print("not printing for some reason")
                        error = 'Invalid Credentials. Please try again.'
                    elif username == row["username"] and passw == row["pword"]:
                        if row['verify'] == '1':
                            session['logged_in'] = username
                            session['uid'] = row['userid']
                            query("UPDATE user SET verify = '2' WHERE username = %s", (username,))
                            return redirect(url_for('editprofile'))
                    else:
                        print("not printing for some reason")
                        error = 'Invalid Credentials. Please try again.'
            else:
                error = "Account not found, please register"
    return render_template('index.html', error=error, title='Login/Register', logged_in=session.get('logged_in'))


@app.route('/register', methods=['GET', 'POST'])
def register():
    error = ""
    if session.get('logged_in'):
        return browse()
    else:
        if request.method == 'GET':
            error = exists(request.args.get('email'), request.args.get('code'))
            print(error)
        elif request.method == 'POST':
            username = html.escape(request.form['unamesignup'])
            firstname = html.escape(request.form['fnamesignup'])
            lastname = html.escape(request.form['lnamesignup'])
            email = html.escape(request.form['emailsignup'])
            location = html.escape(request.form['location'])
            if not location:
                location = getadd()
            code = get_hash(username)
            res = query("""SELECT username FROM User WHERE username = %s""", (username,))
            if re.match(r"[^@\s]+@[^@\s]+\.[a-zA-Z0-9]+$", email):
                if request.form['passwordsignup'] == request.form['passwordsignup_confirm']:
                    if re.match(
                            r'^(?=.*\d)(?=.*[@#\-_$%^&+=§!])(?=.*[a-z])(?=.*[A-Z])([0-9A-Za-z@#\-_$%^&+=§!]{6,20})$',
                            request.form['passwordsignup_confirm']):
                        passw = get_hash(request.form['passwordsignup'])
                        if res:
                            error = "Please select a username as unique as you are"
                            print(error)
                        else:
                            query(
                                """INSERT INTO User (firstname, lastname, username, email, pword, location, token) VALUES(%s,%s,%s,%s,%s,%s,%s)""",
                                (firstname, lastname, username, email, passw, location, code,))
                            error = verify(username, email, code)
                    else:
                        error = "Ooops! Let's try that again, make sure you have at-least one uppercase, lowercase and special character\nMake it 6 characters or longer"
                        print(error)
                else:
                    error = "Please verify password"
                    print(error)
            else:
                error = "Error: was that a proper e-mail? please try again"
                print(error)
    return render_template('index.html', error=error, title='Login/Register', logged_in=session.get('logged_in'))


@app.route('/profile', methods=['GET', 'POST'])
def profile():
    error = None
    if not session.get('logged_in'):
        return login()
    else:
        return render_template('profile.html', error=error, title='Profile', logged_in=session.get('logged_in'))


@app.route('/editprofile', methods=['GET', 'POST'])
def editprofile():
    error = ""
    passw = ""
    res = ""
    if not session.get('logged_in'):
        return login()
    else:
        if request.method == 'POST':
            username = html.escape(request.form['uname'])
            fname = html.escape(request.form['fname'])
            lname = html.escape(request.form['lname'])
            email = html.escape(request.form['email'])
            location = html.escape(request.form['location'])
            age = html.escape(request.form['age'])
            gender = html.escape(request.form['gender'])
            sexual_pref = request.form.get('preference')
            # pref = html.escape(sexual_preference)
            interests = html.escape(request.form['interests'])
            bio = html.escape(request.form['bio'])
            # notification = html.escape(request.form['bio'])
            res = query("""SELECT * FROM User WHERE userid= %s""", (session.get('uid'),))
            if re.match(r"[^@\s]+@[^@\s]+\.[a-zA-Z0-9]+$", email):
                if request.form['pass'] == request.form['confirmpass']:
                    if re.match(
                            r'^(?=.*\d)(?=.*[@#\-_$%^&+=§!\?])(?=.*[a-z])(?=.*[A-Z])([0-9A-Za-z@#\-_$%^&+=§!\?]{6,20})$',
                            request.form['confirmpass']):
                        passw = get_hash(request.form['pass'])
                    else:
                        error = "Ooops! Let's try that again, make sure you have at-least one upercase, lowercase and special character\nMake it 6 characters or longer"
                        print(error)
                else:
                    error = "Please verify password"
                    print(error)
            else:
                error = "Error: was that a proper e-mail? please try again"
                print(error)
            if res:
                sql = "UPDATE User SET "
                if fname:
                    query(sql + "firstname = %s WHERE userid = %s", (fname, session.get('uid'),))
                if lname:
                    query(sql + "lastname = %s WHERE userid = %s", (lname, session.get('uid'),))
                if email:
                    query(sql + "email = %s WHERE userid = %s", (email, session.get('uid'),))
                if passw:
                    query(sql + "pword = %s WHERE userid = %s", (passw, session.get('uid'),))
                if location:
                    query(sql + "location = %s WHERE userid = %s", (location, session.get('uid'),))
                if gender:
                    query(sql + "sex = %s WHERE userid = %s", (gender, session.get('uid'),))
                if age:
                    query(sql + "age = %s WHERE userid = %s", (age, session.get('uid'),))
                if bio:
                    query(sql + "description = %s WHERE userid = %s", (bio, session.get('uid'),))
                if sexual_pref:
                    query(sql + "sexual_pref = %s WHERE userid = %s", (sexual_pref, session.get('uid'),))
                if interests:
                    query(sql + "interests = %s WHERE userid = %s", (interests, session.get('uid'),))
                error = "SUCCESS! update, successful"
        return render_template('EditProfile.html', error=error, title='Account', logged_in=session.get('logged_in'),
                               res=res)


@app.route('/search', methods=['GET', 'POST'])
def dosearch():
    error = ""
    if not session.get('logged_in'):
        return login()
    else:
        if request.method == 'POST':
            print("here")
            username = request.form.get('uname')
            location = request.form.get('location')
            age = request.form.get('age')
            sexual_preference = request.form.get('preference')
            interest = request.form.get('interests')
            fame = request.form.get('fame')
            # pref = html.escape(sexual_preference)
            error = rsearch(username, age, fame, location, interest, sexual_preference)
            print(error)
    return render_template('search.html', error=error, title='search', logged_in=session.get('logged_in'))


@app.route("/logout")
def logout():
    query("UPDATE user SET verify = '1' WHERE username = %s", (session['logged_in'],))
    session['logged_in'] = False
    return login()


@app.route("/forgot_pw", methods=['GET', 'POST'])
def forgot():
    error = ''
    if request.method == 'POST':
        error = reset(request.form['txtemail'])
    return render_template('forgot_pw.html', error=error, title='forgotten password',
                           logged_in=session.get('logged_in'))


@app.route("/change_pw", methods=['GET', 'POST'])
def change():
    error = ''
    try:
        code = request.args.get('code')
        id_ = request.args.get('id')
        if request.method == 'GET':
            error = check(id_, code)
        elif request.method == 'POST':
            error = change_pw(request.form['pass'], request.form['confirm-pass'], id_)
            flash(error, 'error')

    except Exception as e:
        error = "Error : " + str(e)
    return render_template("reset_pw.html", error=error, title='forgotten password', logged_in=session.get('logged_in'))


def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS


@app.route('/upload', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        # if user does not select file, browser also
        # submit a empty part without filename
        if file.filename == '':
            flash('No selected file')
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
            return redirect(url_for('/upload',
                                    filename=filename))
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form method=post enctype=multipart/form-data>
      <p><input type=file name=file>
         <input type=submit value=Upload>
    </form>
    '''


if __name__ == '__main__':
    app.debug = True
    app.run()
