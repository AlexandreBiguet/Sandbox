def any_of(string, predicate):
    for c in string:
        if predicate(c):
            return True
    return False


if __name__ == '__main__':
    s = 'qA2'
    print(any_of(s, lambda c: c.isalnum()))
    print(any_of(s, lambda c: c.isalpha()))
    print(any_of(s, lambda c: c.isdigit()))
    print(any_of(s, lambda c: c.islower()))
    print(any_of(s, lambda c: c.isupper()))
