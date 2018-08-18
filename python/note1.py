"""
I came across a weird warning in pycharm about 'default argument
value is mutable'. This is a test file to understand...

Class variables and default arguments are created when the function is loaded
(and only once), that means that any changes to a "mutable default argument"
or "mutable class variable" are permanent

"""


def func(ilist=[1, 2, 3]):

    print('number of element in the input list : ', len(ilist),
          '\n', 'With values : ')

    for element in ilist:
        print(element)

    ilist.append(4)


def main():
    func()
    func()


if __name__ == '__main__':
    main()
