"""
Basic operations
- arithmetic operations
     Arithmetic operators on arrays apply element-wise. A new array is
     created and filled with the result.
     * using np.ndarray.all
     * using np.ndarray.any
- universal functions (some examples)
  see the doc https://docs.scipy.org/doc/numpy/reference/ufuncs.html for more
  information
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
    arr = np.arange(30).reshape((2, 3, 5))
    print('\n\n', arr, '\n')

    # axis = None -> the min over all element of input array
    print('[axis:{}] [min: {}]\n'.format(None, arr.min(axis=None)))

    for i in range(arr.ndim):
        print('[axis:{}] [mins:\n{}]\n'.format(i, arr.min(axis=i)))


def ufunc_add():
    # np.add
    # Add arguments element-wise.
    # returns ndarray or scalar
    s1 = 2
    s2 = 3
    print('s1 = ', s1, '\ns2 = ', s2)
    print('s1 + s2 = ', np.add(s1, s2))
    a1 = np.arange(10)
    a2 = np.arange(10, 20)
    print('a1 : ', a1, '\na2 : ', a2)
    print('a1 + a2 : ', np.add(a1, a2))
    print('s1 + a1 : ', np.add(s1, a1))
    print('a1 + s1 : ', np.add(a1, s1))


def ufunc_subtract():
    s1 = 2
    s2 = 3
    print('s1 = ', s1, '\ns2 = ', s2)
    print('s1 - s2 = ', np.subtract(s1, s2))
    a1 = np.arange(10)
    a2 = np.arange(10, 20)
    print('a1 : ', a1, '\na2 : ', a2)
    print('a1 - a2 : ', np.subtract(a1, a2))
    print('s1 - a1 : ', np.subtract(s1, a1))
    print('a1 - s1 : ', np.subtract(a1, s1))


def ufunc_multiply():
    s1 = 2
    s2 = 3
    print('s1 = ', s1, '\ns2 = ', s2)
    print('s1 x s2 = ', np.multiply(s1, s2))
    a1 = np.arange(10)
    a2 = np.arange(10, 20)
    print('a1 : ', a1, '\na2 : ', a2)
    print('a1 x a2 : ', np.multiply(a1, a2))
    print('s1 x a1 : ', np.multiply(s1, a1))
    print('a1 x s1 : ', np.multiply(a1, s1))


def ufunc():
    ufunc_add()
    print('\n')
    ufunc_subtract()
    print('\n')
    ufunc_multiply()

    # arr = np.arange(10).reshape(2, 5)
    # print('exp [ ', arr, ' = ', np.exp(arr))
    # arr = np.arange(10)
    # print('sqrt [ ', arr, '] = ', np.sqrt(arr))


def main():
    arit()
    unary()
    unary_with_axis()
    ufunc()


if __name__ == '__main__':
    main()
