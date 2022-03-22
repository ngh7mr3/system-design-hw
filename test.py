import requests as r
import argparse
import random
import string

parser = argparse.ArgumentParser(description='Integration server tests')
parser.add_argument('--host', metavar='host', type=str, default='localhost')
parser.add_argument('--port', metavar='port', type=str, default='8080')


def rnd_s(length: int):
    return ''.join([random.choice(string.ascii_letters) for i in range(length)])


def test_wrapper(test):
    def wrapper(*args, **kwargs):
        print(f'{test.__name__}...', end=' ')
        test(*args, **kwargs)
        print('OK')

    return wrapper


def test_person_scheme(base_url):
    url = f'{base_url}/person'
    print(f'Testing {url}')

    @test_wrapper
    def test_get_person():
        req = r.get(url, params=dict(login='admin'))
        assert req.status_code == r.codes.ok
        assert req.json()['login'] == 'admin'

    @test_wrapper 
    def test_search_person():
        req = r.get(url, params=dict(first_name='foo', last_name='bar'))
        assert req.status_code == r.codes.ok
        assert len(req.json()) == 1
        assert req.json()[0]['login'] == 'admin'

        req = r.get(url, params=dict(first_name='name', last_name='name'))
        assert req.status_code == r.codes.ok
        assert len(req.json()) == 0
        
        req = r.get(url, params=dict(login='admin', first_name='foo'))
        assert req.status_code == r.codes.bad_request
    
    @test_wrapper
    def test_add_new_person():
        req = r.post(url, params=dict(login='admin'))
        assert req.status_code == r.codes.bad_request

        USER_VALID = dict(login=rnd_s(5), first_name=rnd_s(5), last_name=rnd_s(5), age=20)
        USER_NONVALID = dict(login='admin', first_name='foo', last_name='bar', age=-20)

        req = r.post(url, params=USER_VALID)
        assert req.status_code == r.codes.ok

        req = r.get(url, params=dict(login=USER_VALID['login']))
        assert req.json() == USER_VALID

        req = r.post(url, params=USER_NONVALID)
        assert req.status_code == r.codes.bad_request

    test_get_person()
    test_search_person()
    test_add_new_person()


if __name__ == '__main__':
    args = parser.parse_args()
    base_url = f'http://{args.host}:{args.port}'

    test_person_scheme(base_url)
