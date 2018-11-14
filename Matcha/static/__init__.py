from flask import Flask
from config.setup import setup

setup()
print('Setup?')
app = Flask(__name__)
app.secret_key = "7h1$/H0u$3\b17ch1n'"