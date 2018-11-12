from flask import Flask, render_template, redirect, url_for, request, session
import os, re, hashlib
from db import query
from setup import setup
from sendmail import sendmail

app = Flask(__name__)
app.secret_key = "7h1$/H0u$3\b17ch1n'"


def get_hash(code):
    hashcode = code.encode('utf-8')
    return hashlib.sha224(hashcode).hexdigest()


@app.route('/')
def home():
    if not session.get('logged_in'):
        setup()
        return login()
    else:
        return browse()


@app.route('/home')
def browse():
    if not session.get('logged_in'):
        return login()
    else:
        return render_template('home.html', title='Home', logged_in=session.get('logged_in'))


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
            username = request.form['username']
            passw = get_hash(request.form['password'])
            res = query("SELECT * FROM User WHERE username = '{}' AND pword = '{}'".format(username, passw))
            if res:
                for row in res:
                    if username != row[3] or passw != row[5]:
                        print("not printing for some reason")
                        error = 'Invalid Credentials. Please try again.'
                    elif username == row[3] and passw == row[5]:
                        session['logged_in'] = username
                        print(session['logged_in'])
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
        if request.method == 'POST':
            username = request.form['unamesignup']
            firstname = request.form['fnamesignup']
            lastname = request.form['lnamesignup']
            email = request.form['emailsignup']
            location = "somewhere, will create this soon"
            code = get_hash(username)
            res = query("SELECT username FROM User WHERE username = '%s'", username)
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
                            sendmail(username, email, "Account Verification",
                                     "Please follow link to verify your account, before you log in. <href>")
                            query(
                                """INSERT INTO User (firstname, lastname, username, email, pword, location, token) VALUES('{}','{}','{}','{}','{}','{}','{}')""".format(
                                    firstname, lastname, username, email, passw, location, code))
                    else:
                        error = "Ooops! Let's try that again, make sure you have at-least one upercase, lowercase and special character\nMake it 6 characters or longer"
                        print(error)
                else:
                    error = "Please verify password"
                    print(error)
            else:
                error = "was that a proper e-mail? please try again"
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
        return render_template('EditProfile.html', error=error, title='Account', logged_in=session.get('logged_in'))


@app.route("/logout")
def logout():
    session['logged_in'] = False
    return login()


if __name__ == '__main__':
    app.debug = True
    app.run()