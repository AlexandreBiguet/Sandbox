#!/usr/local/bin/python3

# https://www.hackerrank.com/challenges/find-a-string


def count_substring(string, sub_string):
    return sum(string[i:].startswith(sub_string) for i in range(len(string)))


if __name__ == '__main__':
    s = 'ABCDCDC'
    ss = 'CDC'
    print('"{}" appears {} times in "{}"'.format(ss, count_substring(s, ss), s))
