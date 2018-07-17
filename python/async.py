
import socket
from threading import Thread
import asyncio
from abc import ABCMeta, abstractmethod

# 1) Example with servers

def echo_server(address):
    """
    Single connection accepted server
    :param address: a pair (host, port)
    :return: None
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
    sock.bind(address)
    sock.listen(1)
    while True:
        client, addr = sock.accept()
        echo_handler(client, addr)


def echo_handler(client, addr):
    print('Connection from ', addr)
    with client:
        while True:
            data = client.recv(100000)
            if not data:
                break
            client.sendall(data)
    print('Connection closed')


def threaded_echo_server(address):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
    sock.bind(address)
    sock.listen(1)
    while True:
        client, addr = sock.accept()
        Thread(target=echo_handler, args=(client, addr)).start()


async def async_echo_server(address):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
    sock.bind(address)
    sock.listen(5)
    while True:
        client, addr = sock.accept()
        await echo_client(client, addr)


async def echo_client(client, addr):
    print('Connection from ', addr)
    async with client:
        while True:
            data = client.recv(100000)
            if not data:
                break
            await client.sendall(data)
        print('Connection closed')


def server_main():
    address = ('', 25000)
    # echo_server(address)
    # threaded_echo_server(address)
    # asyncio.run(async_echo_server(address))

#
# 2) Simple stuff with fibonacci stuff

async def fib(n):
    if n < 2:
        return 1
    else:
        return await fib(n-1) + await fib(n-2)


async def fib_main():
    for n in range(10):
        print(await fib(n))

    f = await fib(15)
    d = { }
    d[await fib(4)] = 'bonjour'
    print('f = {} \nd = {}'.format(f, d))
    ## 3.6 allows wait in list comprehension
    nums = [1, 10, 15, 20]
    fib_nums = [await fib(n) for n in nums]
    print('{} -> {} '.format(nums, fib_nums))


#
# 3) async instance, class and static methods

class MyFoo:
    """
    More on instance, class and static methods:
    https://realpython.com/instance-class-and-static-methods-demystified/

    Some special functions may be async (but not the __init__)
    """
    def __init__(self, name):
        self.name = name

    async def instance_method(self):
        print('instance method : ', self.name)

    @classmethod
    async def class_method(cls):
        print('class method')

    @staticmethod
    async def static_method():
        print('static method')

    async def __call__(self, *args, **kwargs):
        print('MyFoo __call__ :: [{}] -- [ - {} - ] '.format(args, kwargs))

#
# 4) A way to async the __init__ is to use metaclass

class MyMetaClass(type):
    async def __call__(cls, *args, **kwargs):
        self = cls.__new__(cls, *args, **kwargs)
        await self.__init__(*args, **kwargs)
        return self

class AClass(metaclass=MyMetaClass):
    async def __init__(self, *args, **kwargs):
        print('async init ... ')
        await asyncio.sleep(2)
        print('async init ... Done')


async def get_aclass():
    return await AClass()

def foo_class_main():
    f = MyFoo('Lol')
    asyncio.run(f.instance_method())
    asyncio.run(f.static_method())
    asyncio.run(MyFoo.class_method())
    asyncio.run(f(12, 14, bonjour=12))
    asyncio.run(get_aclass())

#
# 5) it is possible to ensure that some methods are async using abstract base
#     class

class MyABCClass(metaclass=ABCMeta):

    @abstractmethod
    async def cool(self):
        pass

class MyClass(MyABCClass):
    async def cool(self):
        print('that is cool')

class MyOtherClass(MyABCClass):
    def cool(self):
        print('that is not cool')

async def abstract_class_main():
    m = MyClass()
    await m.cool()
    try :
        o = MyOtherClass()
        o.cool()
    except TypeError as e:
        print(e)

def main():
    # server_main()
    # asyncio.run(fib_main())
    # foo_class_main()
    asyncio.run(abstract_class_main())



if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted by user')

