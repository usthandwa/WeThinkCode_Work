#!/usr/bin/python3

import smtplib
from email.mime.text import MIMEText


def sendmail(user, email, subject, msg):

    sender = 'noreply@matcha.com'
    receivers = [email]
    title = 'Matcha | Notification <br><br> \n' \
            '{}'.format(msg)
    msg_content = '<h2>{title} > <br>\n<font color="green">OK</font></h2>\n'.format(title=title)
    message = MIMEText(msg_content, 'html')

    message['From'] = 'Matcha <{}>' .format(sender)
    message['To'] = '{} <{}>' .format(user, email)
    message['Subject'] = subject

    msg_full = message.as_string()

    try:
        smtpObj = smtplib.SMTP('smtp.gmail.com', 587)
        smtpObj.starttls()
        smtpObj.login('usthandwa@gmail.com', '1love4you2')
        smtpObj.sendmail(sender, receivers, msg_full)
        print("Successfully sent email")
        smtpObj.quit()

    except smtplib.SMTPException as e:
        print("Error: unable to send email " + str(e))
