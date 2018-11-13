import MySQLdb
from config import get_config

config_db = get_config()
conn = None

# def _connect(): 

def get_db():
    return config_db['db']


def query(sqlStr):
    conn = MySQLdb.connect(host=config_db['hostname'], user=config_db['username'], passwd=config_db['password'])
    cur = conn.cursor(MySQLdb.cursors.DictCursor)
    content = ""
    if not sqlStr.startswith('CREATE DATABASE'):
        cur.execute("USE Matcha")
    cur.execute(sqlStr)
    content = cur.fetchall()
    conn.commit()
    conn.close()
    return content

