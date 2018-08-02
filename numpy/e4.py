"""
Basic operations
- arithmetic operations
     Arithmetic operators on arrays apply element-wise. A new array is
     created and filled with the result.
     * using np.ndarray.all
     * using np.ndarray.any

"""

import numpy as np


def arit():
    a = np.array([1, 2, 3, 4], dtype=int)
    print('A = ', a, '\n')

    b = np.ones(1, dtype=int)
    print('B = ', b, '\n')

    c = a+b
    print('should be 2, 3, 4, 5 : \n C = ', c, '\n')

    d = np.array([1, 2, 3, 4], dtype=int)
    d += 1
    print('should be equal to C \n D = ', d, '\n')

    z = c-d
    print('should be full of zeros\n Z = ', z, '\n')

    a_squared = a**2
    print('A^2 = ', a_squared, '\n')

    bool_array = a_squared > 2
    print('Bool array [A^2]_i > 2 : ', bool_array, '\n')

    if bool_array.all():
        print('every element of A^2 array are > 2 [using np.ndarray.all()]')
    else:
        print('some element of A^2 array are < 2 [using np.ndarray.all()]')

    if (a_squared > 3).any():
        print('some element of A^2 are > 3')
    else:
        print('every element of A^2 are < 3')

    # Sum of different array is possible if they have the same number
    # of element
    print('sum of ones + linspace : ',
          np.ones(3) + np.linspace(0, np.pi, 3), '\n')


def unary():
    rngd = np.random.random((3, 3))
    print('Random array : \n R1 = \n', rngd, '\n')

    # random array composed of float [-10, 10]
    low = -10.0
    high = +10.0

    rngd_lh = (rngd * (high - low)) + low

    print('Random array \in [-10, 10]: \n R2 = \n', rngd_lh, '\n')

    print('min values    [R1: {: <+12.7f}] [R2: {: <+12.7f}]'
          .format(rngd.min(), rngd_lh.min()))

    print('max values    [R1: {: <+12.7f}] [R2: {: <+12.7f}]'
          .format(rngd.max(), rngd_lh.max()))

    print('mean values   [R1: {: <+12.7f}] [R2: {: <+12.7f}]'
          .format(rngd.mean(), rngd_lh.mean()))

    print('sum of values [R1: {: <+12.7f}] [R2: {: <+12.7f}]'
          .format(rngd.sum(), rngd_lh.sum()))


def unary_with_axis():
    arr = np.arange(60).reshape((2, 2, 3, 5))
    print('\n\n', arr, '\n')

    # axis = None -> the min over all element of input array
    print('[axis:{}] [min: {}]\n'.format(None, arr.min(axis=None)))

    for i in range(arr.ndim):
        print('[axis:{}] [row mins:\n{}]\n'.format(i, arr.min(axis=i)))


def main():
    arit()
    unary()
    unary_with_axis()


if __name__ == '__main__':
    main()
