#!/usr/local/bin/python3

# https://www.hackerrank.com/challenges/swap-case/


def swap_case(s):
    ns = ''
    for c in s:
        if c.isupper():
            ns += c.lower()
        elif c.islower():
            ns += c.upper()
        else:
            ns += c
    return ns


if __name__ == '__main__':
    s = 'HackerRank.com presents "Pythonist 2".'
    print(s)
    ns = swap_case(s)
    print(s, '  -->  ', ns)
