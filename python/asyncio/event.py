"""
Testing asyncio Event loop stuff
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
# 18.5.1.18.1. Hello World with call_soon()

def call_soon():
    def hello_world(loop):
        print('Hello World')
        loop.stop()

    loop = asyncio.get_event_loop()

    # Schedule a call to hello_world()
    loop.call_soon(hello_world, loop)

    # Blocking call interrupted by loop.stop()
    loop.run_forever()
    loop.close()


# -----------------------------------------------------------------------------
# 18.5.1.18.2. Display the current date with call_later()

def call_later():

    def display_date(end_time, loop):
        print(datetime.datetime.now())
        if (loop.time() + 1.0) < end_time:
            loop.call_later(1, display_date, end_time, loop)
        else:
            loop.stop()

    loop = asyncio.get_event_loop()

    # Schedule the first call to display_date()
    end_time = loop.time() + 5.0
    loop.call_soon(display_date, end_time, loop)

    # Blocking call interrupted by loop.stop()
    loop.run_forever()
    loop.close()


# -----------------------------------------------------------------------------
# custom function 1
def custom1():
    """
    Prints [Hello, World] every seconds

    Prints [Something] every 3 seconds

    Prints [GoodBye] after 20 seconds and stops the program

    ^C to kill the program

    Note : It is quite weird that i can push callback in the loop whereas
    the loop variable is defined at outer scope..

    Question :
    main program, running this function in a debugger. Pausing the
    program for a duration > 20 seconds will only prints 'GoodBye' to stdout.
    I would have expected that pausing the program would postpone all, or, at
    least I don't really understand why the 'Goodbye' got printed

    :return: None
    """

    loop = asyncio.get_event_loop()

    def hello(something_called=False):
        _logger.info("Hello, World [Every second]")
        loop.call_later(1.0, hello, True)
        if not something_called:
            loop.call_soon(something)
            # Ok to call here since we enter this if loop only once
            loop.call_later(20.0, good_bye)

    def something():
        _logger.info("Something [Every 3 seconds]")
        loop.call_later(3.0, something)

    def good_bye():
        _logger.info("GoodBye")
        loop.stop()

    loop.call_soon(hello, False)
    loop.run_forever()
    loop.close()


# -----------------------------------------------------------------------------
# custom 2 : trying to understand the custom 1 / question
def custom2(sleeping_time=0.0, do_sleep=False):
    """
    I'm new python and asyncio and python debugger stuff.
    I just want to try to call a custom1.good_bye and 1 second after call a
    blocking sleeping function

    Note : Well, once the blocking wait is ended, the last task is performed.
    Depending on the time waiting, we may say other task to be performed

    :param sleeping_time : time in second to sleep (only active if
    do_sleep is True)

    :param do_sleep : If True, then blocking sleep for sleeping_time seconds

    :return: None
    """

    loop = asyncio.get_event_loop()

    def good_bye():
        _logger.info("GoodBye")
        loop.stop()

    def hello(should_call, should_wait):

        if should_call:
            loop.call_later(10.0, good_bye)
            loop.call_later(1.0, hello, False, True)
            return

        _logger.info("Hey, there")

        if should_wait:
            _logger.info("blocking wait : started [only one time]")
            if do_sleep:
                time.sleep(sleeping_time)
            _logger.info("blocking wait : ended [only one time]")

        loop.call_later(1.0, hello, False, False)

    _logger.info("Starting ... ")
    loop.call_soon(hello, True, False)

    loop.run_forever()
    loop.close()


# -----------------------------------------------------------------------------
# main function
# -----------------------------------------------------------------------------
def main():
    # call_soon()
    # call_later()
    # custom1()
    custom2()


if __name__ == "__main__":

    def on_exit(sig_name):
        print("got signal %s: exit" % sig_name)
        loop.stop()

    loop = asyncio.get_event_loop()
    for sig_name in ('SIGINT', 'SIGTERM'):
        loop.add_signal_handler(getattr(signal, sig_name),
                                functools.partial(on_exit, sig_name))

    try:
        # loop.run_forever()
        main()
    finally:
        loop.close()
