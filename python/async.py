
import socket
from threading import Thread
import asyncio


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
    # async with client:
    while True:
        data = client.recv(100000)
        if not data:
            break
        await client.sendall(data)
    print('Connection closed')


def main():
    address = ('', 25000)
    # echo_server(address)
    # threaded_echo_server(address)
    asyncio.run(async_echo_server(address))


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted by user')

