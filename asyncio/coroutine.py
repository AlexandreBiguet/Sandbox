"""
Testing asyncio coroutine stuffs
"""
import asyncio
import datetime
import logging
import sys
import time
import functools
import os
import signal


log_format = "[%(asctime)s.%(msecs)03d] [%(name)s] %(levelname)s : %(message)s"
logging.basicConfig(level=logging.DEBUG, stream=sys.stdout,
                    format=log_format, datefmt="%H:%M:%S")

_logger = logging.getLogger(__name__)


# -----------------------------------------------------------------------------
# Hello world example
def hello_world():
    """
    This is the simple hello world example from
    """
    async def local_hello():
        _logger.info("Hello, World")

    a_loop = asyncio.get_event_loop()

    # Blocking call which returns when the local_hello() co-routine is done
    a_loop.run_until_complete(local_hello())
    a_loop.close()


# -----------------------------------------------------------------------------
# custom hello world
def more_hello_world():

    a_loop = asyncio.get_event_loop()

    async def local_hello():
        _logger.debug("Should see 3 coucous and 1 Hello")
        await asyncio.sleep(3.0)
        _logger.info("Hello, World")

    def coucou():
        _logger.debug("coucou")
        a_loop.call_later(1.0, coucou)

    async def start_coucouing():
        _logger.debug("Ready to coucou")
        a_loop.call_soon(coucou)

    a_loop.run_until_complete(asyncio.gather(local_hello(), start_coucouing()))
    a_loop.close()


# -----------------------------------------------------------------------------
# Current date display
def current_date_display(loop):

    async def display_date(local_loop):
        end_time = local_loop.time() + 5.0
        while True:
            print(datetime.datetime.now())
            if (local_loop.time() + 1.0) == end_time:
                _logger.debug("breaking now")
                break
            await asyncio.sleep(1)

    # Blocking call which returns when the display_date() co-routine is done
    loop.run_until_complete(display_date(loop))
    loop.close()

# -----------------------------------------------------------------------------
# main function
# -----------------------------------------------------------------------------
def main(loop):
    # hello_world()
    # more_hello_world()
    current_date_display(loop)


if __name__ == "__main__":

    def on_exit(sig_name):
        n = 0
        for task in asyncio.Task.all_tasks():
            _logger.debug("Cancelling task {} ".format(n))
            n = n+1
            task.cancel()
        print("got signal %s: exit" % sig_name)
        loop.stop()

    loop = asyncio.get_event_loop()

    for sig_name in ('SIGINT', 'SIGTERM'):
        loop.add_signal_handler(getattr(signal, sig_name),
                                functools.partial(on_exit, sig_name))

    try:
        # loop.run_forever()
        main(loop)
    finally:
        loop.close()
