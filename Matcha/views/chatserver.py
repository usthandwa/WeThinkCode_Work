from flask import render_template, flash, redirect, request, redirect, url_for, flash, abort, g, session, escape, \
    jsonify, Request, Flask, Response, escape
# from app import mysql, mail, Message, socketio, connDb
from flask_socketio import SocketIO, send, join_room, leave_room, close_room, rooms, disconnect
from config.db import query


@app.route('/messages/<surname>/<name>/<ident>')
def messaging(surname, name, ident):
    # if check_url_user(surname, name, ident) == 0:
    #     return redirect(url_for('home'))
    id_matches = query("SELECT id_user2 FROM matches WHERE id_user1 = '" + str(
        session['user_id']) + "' UNION SELECT id_user1 FROM matches WHERE id_user2 = '" + str(session['user_id']) + "'")
    tab_users = []
    for id_match in id_matches:
        user_info = query("SELECT surname, name FROM users WHERE id_user = '" + str(id_match[0]) + "'")
        tab_users.append([id_match[0], user_info[0][0], user_info[0][1]])
    target = {'surname': surname, 'name': name, 'ident': ident}
    user = {'surname': session['user_surname'], 'name': session['user_name'], 'ident': session['user_id']}
    if int(ident) < session['user_id']:
        room = ident + '-' + str(session['user_id'])
    elif session['user_id'] < int(ident):
        room = str(session['user_id']) + '-' + ident
    session['room'] = room
    name = session.get('user_name', '')
    room = session.get('room', '')
    if name == '' or room == '':
        return redirect(url_for('index'))
    all_messages = query(
        "SELECT users.surname, users.name, chat.message FROM users INNER JOIN chat ON users.id_user = chat.id_user WHERE room = '" + room + "'")
    query("UPDATE user_infos SET last_connection = NOW() WHERE id_user = '" + str(session['user_id']) + "'")

    return render_template('discussion.html', page='profile', title='Messagerie', user=session['user_surname'],
                           tab_users=tab_users, u_one=user, target=target, name=name, room=room,
                           all_messages=all_messages, notifs=count_notif(session['user_id']),
                           tab_match=print_match(session['user_id']))


@socketio.on('joined', namespace='/chat')
def joined(message):
    room = session.get('room')
    clients.append(session.get('user_id'))
    join_room(room)
    emit('status', {'msg': str(session.get('user_name')) + ' has entered the room.'}, room=room)


@socketio.on('notif_joined', namespace='/notif')
def notif_joined(message):
    counter = 0
    for client in clients:
        if client == session['user_id']:
            counter += 1
    if counter == 0:
        clients.append(session.get('user_id'))
    n_room = session.get('notif_room')
    join_room(n_room)
    x = connDb.cursor()
    x.execute("(SELECT id_user1 FROM matches WHERE id_user2 = '" + str(
        session["user_id"]) + "') UNION (SELECT id_user2 FROM matches WHERE id_user1 = '" + str(
        session["user_id"]) + "')")
    id_u_match = x.fetchall()
    for id_user in id_u_match:
        emit('status', {'msg': ' is connected', 'target': str(session.get("user_id"))}, room=id_user[0])


@socketio.on('text', namespace='/chat')
def text(message):
    room = session.get('room')
    msg = message['msg'];
    emit('message', {'msg': session.get('user_surname') + ' a ecrit: ' + message['msg']}, room=room)
    x = connDb.cursor()
    req = "INSERT INTO chat (id_user, message, room) VALUES (%s, %s, %s)"
    x.execute(req, (session['user_id'], msg, message['room_number']))
    connDb.commit()
    add_notification(str(session['user_id']), "message", str(message['target']))


@socketio.on('left', namespace='/chat')
def left(message):
    room = session.get('room')
    leave_room(room)
    emit('status', {'msg': session.get('user_name') + ' has left the room.'}, room=room)


@socketio.on('discon')
def socket_disco(ident):
    for client in clients:
        if client == ident:
            clients.remove(ident)


@socketio.on('disconnect')
def disconnect():
    for client in clients:
        if client == session['user_id']:
            clients.remove(session['user_id'])
