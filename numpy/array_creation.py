"""
array creation

from : https://docs.scipy.org/doc/numpy/reference/routines.array-creation.html


"""

import numpy as np


_line_width = 80


def func_name_printer(the_function):
    """
    decorator used to print split functions calls
    :param the_function: function to be decorated
    :return: the wrapped function
    """
    def wrap():
        print('-' * _line_width)
        print('-- Array creation : ',
              the_function.__name__, ' : Begin --', '\n')
        the_function()
        print('\n', '-- ', the_function.__name__, ' : End --', '\n')
    return wrap


@func_name_printer
def np_empty():
    """
    using numpy.empty(shape, dtype=float, order='C')
          Return a new array of given shape and type, without initializing
          entries.

    :return: None
    """

    a = np.empty((2, 2))
    print('a floating type empty 2x2 array : \n', a, '\n')

    a = np.empty((2, 4), dtype=np.int8)
    print('a numpy.int8 type empty 2x4 array : \n', a, '\n')


@func_name_printer
def np_empty_like():
    """
    using numpy.empty_like(prototype, dtype=None, order='K', subok=True)
          Return a new array with the same shape and type as a given array.

    :return: None
    """

    arr = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]], dtype=np.int8)
    print('input array : \n', arr, '\n')

    em = np.empty_like(arr, dtype=np.float16)
    print('empty array, (float type) like input array: \n', em, '\n')

    em = np.empty_like(arr, dtype=np.int8)
    print('empty array, (np.int8 type) like input array: \n', em, '\n')


@func_name_printer
def np_eye():
    """
    using numpy.eye(N, M=None, k=0, dtype=<class 'float'>, order='C')
          returns a 2-D array with ones on the diagonal and zeros elsewhere.

    :return: None
    """

    n_rows = 4
    n_cols = 5

    diagonal_mat = np.eye(N=n_rows, M=n_cols, k=0, dtype=np.int8)
    print('diagonal matrix with shape : ', diagonal_mat.shape,
          '\n', diagonal_mat, '\n')

    diagonal_mat = np.eye(N=5, k=0, dtype=int)
    print('5x5 diagonal matrix: \n', diagonal_mat, '\n')

    upper_diag_mat = np.eye(N=4, k=1, dtype=int)
    print('4x4 upper diag matrix: \n', upper_diag_mat, '\n')

    print(' * creating an upper triangle array using np.eye array creator')
    mat = np.zeros((4, 4), dtype=int)
    n = min(mat.shape[0], mat.shape[1])
    for i in range(n):
        up = np.eye(N=n, k=i, dtype=int)
        mat = mat + up

    print('output : \n', mat, '\n')


@func_name_printer
def np_identity():
    """
    using numpy.identity(n, dtype=None)[source]
          returns the identity array.
    :return: None
    """
    identity = np.identity(5, dtype=int)
    print('identity array : \n', identity, '\n')


@func_name_printer
def np_ones():
    """
    using numpy.ones(shape, dtype=None, order='C')
          returns a new array of given shape and type, filled with ones.
    :return: None
    """

    ones = np.ones(5, dtype=int)
    print('line array (5 elements) : ', ones, '\n')

    ones = np.ones((5, 4), dtype=int)
    print('array ', ones.shape, ' : \n', ones, '\n')

    ones = np.ones((5, 1), dtype=int)
    print('col array of ones : \n', ones, '\n')

@func_name_printer
def np_ones_like():
    """
    using numpy.ones_like(a, dtype=None, order='K', subok=True)
          Return an array of ones with the same shape and type as a given array.

    :return: None
    """
    arr = np.arange(6).reshape((3, 2))
    print('input array : \n', arr, '\n')

    ones = np.ones_like(arr)
    print('one like : \n', ones, '\n')

    arr = np.arange(10)
    print('also works with line array: \n', arr, '\n',
          'ones: \n', np.ones_like(arr), '\n')


def main():
    np_empty()
    np_empty_like()
    np_eye()
    np_ones()
    np_ones_like()


if __name__ == '__main__':
    main()
