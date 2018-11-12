from flask import Flask, render_template, redirect, url_for, request, session
import os, re, hashlib
from db import query
from setup import setup
from sendmail import sendmail
setup()
app = Flask(__name__)
app.secret_key = "7h1$/H0u$3\b17ch1n'"