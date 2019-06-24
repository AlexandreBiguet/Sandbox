#!/usr/local/bin/python3

# https://www.hackerrank.com/challenges/python-string-split-and-join


def split_and_join_2(line):
    # write your code here
    res = ''
    for c in line:
        if c == ' ':
            res += '-'
        else:
            res += c
    return res


def split_and_join(line):
    arr = line.split(' ')
    return '-'.join(arr)


if __name__ == '__main__':
    s = 'this is a string'
    print(s, '  -->  ', split_and_join(s))
