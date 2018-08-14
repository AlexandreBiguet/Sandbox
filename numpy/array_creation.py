"""
array creation

from : https://docs.scipy.org/doc/numpy/reference/routines.array-creation.html

no brain, just following the routine list

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


@func_name_printer
def np_zeros():
    """
    using numpy.zeros(shape, dtype=float, order='C')¶
          Return a new array of given shape and type, filled with zeros.

    :return: None
    """
    zer = np.zeros(5)
    print('line array of zeros : \n', zer, '\n')

    zer = np.zeros((5, 3))
    print('array (shape', zer.shape, ') : \n', zer, '\n')


@func_name_printer
def np_zeros_like():
    """
    using numpy.zeros_like(a, dtype=None, order='K', subok=True)
          Return an array of zeros with the same shape and type as a
          given array.

    :return: None
    """

    arr = np.arange(6).reshape((3, 2))
    print('input array : \n', arr, '\n')

    ones = np.zeros_like(arr)
    print('one like : \n', ones, '\n')

    arr = np.arange(10)
    print('also works with line array: \n', arr, '\n',
          'ones: \n', np.zeros_like(arr), '\n')


@func_name_printer
def np_full():
    """
    using numpy.full(shape, fill_value, dtype=None, order='C')
          Return a new array of given shape and type, filled with fill_value.

    :return: None
    """

    value = 10
    arr = np.full(5, value, dtype=int)
    print('line array filled with ', value, '\n', arr, '\n')

    arr = np.full(5, value, dtype=np.float16)
    print('same array but float type ', value, '\n', arr, '\n')

    value = np.nan
    arr = np.full((5, 5), value, dtype=float)
    print('array shape: ', arr.shape, ' filled with ', value, '\n', arr, '\n')


@func_name_printer
def np_full_like():
    """
    using numpy.full_like(a, fill_value, dtype=None, order='K', subok=True)
          Return a full array with the same shape and type as a given array.

    :return: None
    """

    arr = np.arange(0.0, 20.0, 2).reshape(2, 5)
    print('init array (dtype :', arr.dtype, ') \n', arr, '\n')

    value = 10
    ful = np.full_like(arr, value, dtype=np.int8)
    print('full_like array (dtype :', ful.dtype,
          ') (value : ', value, ') \n', ful, '\n')

    print('what happens if value is > than max of type ?'
          ' type change or cycle ? ')
    value = 128
    ful = np.full_like(arr, value, dtype=np.int8)
    print('full_like array (dtype :', ful.dtype,
          ') (value : ', value, ') \n', ful, '\n')


@func_name_printer
def np_array():
    """
    using
    numpy.array(object, dtype=None, copy=True, order='K', subok=False, ndmin=0)
    Create an array.

    :note: see the doc for more information about parameters

    :return: None
    """
    arr = np.array([1, 2, 3])
    print('array creation from list: \n', arr, '\n')

    arr = np.array([10, 20, 30.0])
    print('array creation (upcasting) to float \n', arr, '\n')

    arr = np.array([[1, 2, 3], [4, 5, 6]])
    print('two dim. array \n', arr, '\n')

    arr = np.array([1, 2, 3, 4], ndmin=2)
    print('creation of an array with minimum 2 dimensions : \n', arr, '\n')

    arr = np.array([1, 2, 3, 4], ndmin=4, dtype=complex)
    print('creation of an array with minimum 4 dimensions (dtype :',
          arr.dtype, ') : \n', arr, '\n')

    # subok parameter:
    # If True, then sub-classes will be passed-through, otherwise the returned
    # array will be forced to be a base-class array (default).

    arr = np.array(np.mat('1 2 ; 3 4'), subok=False)
    print('creation of an array from a array subclass (matrix).\nArray type : ',
          type(arr), '\n', arr, '\n')

    arr = np.array(np.mat('1 2 ; 3 4'), subok=True)
    print('creation of an array from a array subclass (matrix).\nArray type : ',
          type(arr), '\n', arr, '\n')


@func_name_printer
def np_asarray():
    a_list = [1, 2]
    arr = np.asanyarray(a_list)
    print('input list : ', a_list, ' as numpy array : ', arr, '\n')

    a_list_of_list = [[1, 2, 3], [4, 5, 6]]
    arr = np.asanyarray(a_list_of_list)
    print('input list of list : \n', a_list_of_list,
          '\n', 'as a np array: \n', arr, '\n')

    a_tuple = (1, 2, 3)
    arr = np.asanyarray(a_tuple)
    print('input tuple : ', a_tuple, 'as a numpy array : ', arr, '\n')

    a_tuple_of_tuple = ((1, 2), (3, 4))
    arr = np.asanyarray(a_tuple_of_tuple)
    print('input tuple of tuple : \n', a_tuple_of_tuple,
          '\n', 'as a np array: \n', arr, '\n')


def main():
    np_empty()
    np_empty_like()
    np_eye()
    np_ones()
    np_ones_like()
    np_zeros()
    np_zeros_like()
    np_full()
    np_full_like()
    np_array()
    np_asarray()


if __name__ == '__main__':
    main()
