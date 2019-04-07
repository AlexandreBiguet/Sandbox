"""
Using numpy.arange and numpy.reshape

numpy.arange returns an evenly spaced values within a given interval.

numpy.reshape gives a new shape to an array without changing its data.

numpy.linspace returns evenly spaced numbers over a specified interval.
"""

import numpy as np


def main():
    #
    a = np.arange(15)
    print(a, '\n')

    a = a.reshape(3, 5)
    print(a, '\n')

    a = np.arange(0, 15, 2)
    print(a, '\n')

    n_point = 30
    include_endpoint = True
    space = np.linspace(0, 15, num=n_point, endpoint=include_endpoint,
                        retstep=False)
    print(space, '\n')
    print('[shape : {}] [ndim: {}] [nelement: {}] \n'
          .format(space.shape, space.ndim, space.size))

    space, step = np.linspace(0, 2, num=10, endpoint=True, retstep=True)
    print(space, step, '\n')

    space, step = np.linspace(0, 2, num=10, endpoint=False, retstep=True)
    print(space, step, '\n')


if __name__ == '__main__':
    main()
