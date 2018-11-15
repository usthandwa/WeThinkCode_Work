import MySQLdb
from config.config import get_config

config_db = get_config()


def get_db():
    return config_db['db']


def query(sqlStr, *args):
    conn = MySQLdb.connect(host=config_db['hostname'], user=config_db['username'], passwd=config_db['password'])
    cur = conn.cursor(MySQLdb.cursors.DictCursor)
    content = ""
    if not sqlStr.startswith('CREATE DATABASE'):
        cur.execute("USE Matcha")
    print(*args)
    cur.execute(sqlStr, *args)
    content = cur.fetchall()
    conn.commit()
    conn.close()
    return content

