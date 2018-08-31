def fun(x, y):
    return 2.*x + y


def tofile(filename, sep):
    file = open(filename, 'w')
    for x in range(5):
        for y in range(5):
            file.write( str(x) + sep + str(y) + sep + str(fun(x, y)) + '\n')


def fun2(x):
    return x**2


def tofile2d(filename, sep):
    file = open(filename, 'w')
    for x in range(0, 10):
        file.write( str(x) + sep + str(fun2(x)) + '\n')


def main():
    # tofile('space_sep.txt', ' ')
    # tofile('semicol_sep.txt', '; ')

    tofile2d('space_sep.txt', ' ')


if __name__ == '__main__':
    main()
