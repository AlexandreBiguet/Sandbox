#!/opt/local/bin/python
# coding: utf8

# http://stackoverflow.com/questions/2573135/python-progression-path-from-apprentice-to-guru

from itertools import count


def range1(stop_at=0):
    ran = []
    for n in count(0):
        if 0 < stop_at < n:
            return
        for r in ran:
            if r == n:
                break
        ran.append(n)
        yield n


def range2(stop_at=0):
    for n in count(0):
        if 0 < stop_at < n:
            return
        yield n


def range_pair(stop_at=0):
    for n in count(0):
        if 0 < stop_at < n:
            return
        if not n % 2:
            yield n


s = [i for i in range2(3)]
print(s)

s = [i for i in range_pair(10)]
print(s)

s = list(map(lambda x: x**2, range_pair(10)))
print(s)

s = list(filter(lambda x: not x % 2, range1(11)))
print(s)
