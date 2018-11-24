import re

from flask import Flask, render_template, redirect, url_for, request, session, flash

from config.db import query
from config.setup import setup
from views.display_ import get_all
from views.reset import *
from views.functions import *

# from .geodata import get_geodata
#
# add = get_geodata("127.0.0.1")

app = Flask(__name__)
app.secret_key = "7h1$/H0u$3\b17ch1n'"

setup()

@app.route('/')
def home():
    if not session.get('logged_in'):
        return login()
    else:
        return browse()


@app.route('/home')
def browse():
    if not session.get('logged_in'):
        return login()
    else:
        flash("Logged in successfully.")
        result = get_all()
        return render_template('home.html', title='Home', logged_in=session.get('logged_in'), data=result)


# Route for handling the login page logic
@app.route('/search')
def dosearch():
    if not session.get('logged_in'):
        return login()
    else:
        return render_template('search.html', title='Search', logged_in=session.get('logged_in'))


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
                        if row['Verify'] == '1':
                            session['logged_in'] = username
                            flash("Logged in successfully.")
                            return redirect(url_for('browse'))
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
                            r'^(?=.*\d)(?=.*[@#\-_$%^&+=§!\?])(?=.*[a-z])(?=.*[A-Z])([0-9A-Za-z@#\-_$%^&+=§!\?]{6,20})$',
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
                        error = "Ooops! Let's try that again, make sure you have at-least one upercase, lowercase and special character\nMake it 6 characters or longer"
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


@app.route('/EditProfile', methods=['GET', 'POST'])
def editprofile():
    error = None
    if not session.get('logged_in'):
        return login()
    else:
        if request.method == 'POST':
            username = html.escape(request.form['unamesignup'])
            firstname = html.escape(request.form['fnamesignup'])
            lastname = html.escape(request.form['lnamesignup'])
            email = html.escape(request.form['emailsignup'])
            location = html.escape(request.form['location'])
            age = html.escape(request.form['age'])
            gender = html.escape(request.form['gender'])
            sexual_preference = html.escape(request.form['preference'])
            interests = html.escape(request.form['interests'])
            bio = html.escape(request.form['bio'])
            notification = html.escape(request.form['bio'])
            code = get_hash(username)
            res = query("""SELECT username FROM User WHERE username = %s""", (username,))
            if re.match(r"[^@\s]+@[^@\s]+\.[a-zA-Z0-9]+$", email):
                if request.form['passwordsignup'] == request.form['passwordsignup_confirm']:
                    if re.match(
                            r'^(?=.*\d)(?=.*[@#\-_$%^&+=§!\?])(?=.*[a-z])(?=.*[A-Z])([0-9A-Za-z@#\-_$%^&+=§!\?]{6,20})$',
                            request.form['passwordsignup_confirm']):
                        passw = get_hash(request.form['passwordsignup'])
                        if res:
                            error = "Please select a username as unique as you are"
                            print(error)
                        else:
                            query(
                                """INSERT INTO User (firstname, lastname, username, email, pword, location, sex, age, discription, token) VALUES(%s,%s,%s,%s,%s,%s,%s)""",
                                (firstname, lastname, username, email, passw, location, gender, age, bio, code,))
                            error = "SUCCESS! update, successful"
                    else:
                        error = "Ooops! Let's try that again, make sure you have at-least one upercase, lowercase and special character\nMake it 6 characters or longer"
                        print(error)
                else:
                    error = "Please verify password"
                    print(error)
            else:
                error = "Error: was that a proper e-mail? please try again"
                print(error)

        return render_template('EditProfile.html', error=error, title='Account', logged_in=session.get('logged_in'))


@app.route("/logout")
def logout():
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
        if request.method == 'POST':
            error = change_pw(request.form['passwordsignup'], request.form['passwordsignup_confirm'], id_, code)
            flash(error, 'error')
        elif request.method == 'GET':
            error = change_pw(request.form['passwordsignup'], request.form['passwordsignup_confirm'], id_, code)
    except Exception as e:
        error = "Error : " + str(e)
    return render_template("reset_pw.html", error=error, title='forgotten password', logged_in=session.get('logged_in'))


if __name__ == '__main__':
    app.debug = True
    app.run()
