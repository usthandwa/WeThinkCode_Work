import hashlib

config = {
    'hostname': 'localhost',
    'username': 'root',
    'password': 'rootuser',
    'db' : 'Matcha',
}


def get_config():
    return config


def get_hash(code):
    hashcode = code.encode('utf-8')
    return hashlib.sha224(hashcode).hexdigest()
