"""
array creation

from :
https://docs.scipy.org/doc/numpy/reference/routines.array-creation.html

no brain, just following the doc

"""

import numpy as np
from io import StringIO   # StringIO behaves like a file object.


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
    """
    using numpy.asarray(a, dtype=None, order=None)
          Convert the input to an array.

    :return: None
    """

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

    a = np.array([1, 2, 3, 4])
    arr = np.asarray(a)
    print('existing np array are not copied : \n',
          'a = ', a, '\n', 'arr = ', arr, '\n')
    print('arr is a ? : ', arr is a, '\n')

    print('If dtype is set, array is copied only if dtype does not match:')
    a = np.array([1, 2], dtype=np.float32)
    print('a = ', a, '(dtype :', a.dtype, ')')
    print('np.asarray(a, dtype=np.float32) is a : ',
          np.asarray(a, dtype=np.float32) is a)
    print('np.asarray(a, dtype=np.float64) is a : ',
          np.asarray(a, dtype=np.float64) is a)


@func_name_printer
def np_asanyarray():
    """
    using numpy.asanyarray(a, dtype=None, order=None)
         Convert the input to an ndarray, but pass ndarray subclasses through.

    :return: None
    """

    a = ['hi', 'hello']
    arr = np.asanyarray(a)
    print('a : ', a, '\n', 'arr = ', arr, '\n')

    a = np.array([(1.0, 2), (3.0, 4)], dtype='f4,i4').view(np.recarray)
    print('a = ', a, '\n', type(a), '\n', 'np.asanyarray(a) is a : ',
          np.asanyarray(a) is a, '\n')
    print('a = ', a, '\n', type(a), '\n', 'np.asanyarray(a) is a : ',
          np.asarray(a) is a, '\n')


@func_name_printer
def np_ascontinuousarray():
    """
    using numpy.ascontiguousarray(a, dtype=None)
          Return a contiguous array in memory (C order).

    :return: None
    """

    x = np.arange(10000).reshape(100, 100)
    print('x : \n', x, '\n', "x.flags['C_CONTIGUOUS']",
          x.flags['C_CONTIGUOUS'], '\n')
    np.ascontiguousarray(x, dtype=np.float32)
    print('x : \n', x, '\n', "x.flags['C_CONTIGUOUS']",
          x.flags['C_CONTIGUOUS'], '\n')


@func_name_printer
def np_copy():
    """
    using numpy.copy(a, order='K')
          Return an array copy of the given object.

    :return: None
    """

    x = np.ones(5)
    print('x : ', x, '\n')
    y = x
    z1 = np.copy(x)
    z2 = np.array(x, copy=True)
    x[0] = 10
    print('setting x[0] = 10')
    print('x[0] == y[0] : ', x[0] == y[0])
    print('x[0] == z1[0] : ', x[0] == z1[0])
    print('x[0] == z2[0] : ', x[0] == z2[0])


@func_name_printer
def np_frombuffer():
    """
    using numpy.frombuffer(buffer, dtype=float, count=-1, offset=0)
          Interpret a buffer as a 1-dimensional array.

    :return: None
    """

    print('array from buffer')

    string = 'good morning'
    arr = np.frombuffer(string.encode(), dtype='S1')
    print('initial string : ', string, '\n', 'arr : ', arr,
          ' (dtype : ', arr.dtype, ')\n')

    arr = np.frombuffer(b'\x01\x02', dtype=np.uint8)
    print('arr = ', arr, '\n')

    byte = b'\x01\x02\x03\x04\x05'
    print('init bytes : ', byte)
    arr = np.frombuffer(byte, dtype=np.uint8, count=3)
    print('first 3 elements : ', arr, '\n')

    arr = np.frombuffer(byte, dtype=np.uint8, count=3, offset=2)
    print('last three elements', arr, '\n')


@func_name_printer
def np_fromfile():
    dt = np.dtype([('time', [('min', int), ('sec', int)]),
                   ('temp', float)])
    x = np.zeros((1,), dtype=dt)
    x['time']['min'] = 10
    x['time']['sec'] = 5
    x['temp'] = 42.0
    print('custom type array : ', x.dtype, '\n', x, '\n')
    file_name = 'np_fromfile_testfile_tofromfile.npy'
    x.tofile(file_name)
    xp = np.fromfile(file_name, dtype=dt)
    print('array written to file : \n', x, '\n')
    print('array read from file : \n', xp, '\n')

    print('from the doc the recommended way to write and read from file is to '
          'use the save and\n load routines')

    file_name = 'np_fromfile_testfile_saveload.npy'
    np.save(file_name, x)
    xp = np.load(file_name)
    print('array loaded from file : \n', xp, '\n')


@func_name_printer
def np_fromfunction():
    """
    using numpy.fromfunction(function, shape, **kwargs)
        Construct an array by executing a function over each coordinate.
        The resulting array therefore has a value fn(x, y, z)
        at coordinate (x, y, z).

    :return: None
    """

    def f_2d(x, y):
        return x**2 + y + 1.0

    def f_1d(x):
        return x**3

    print('constructing arrays using lambdas or functions')

    arr = np.fromfunction(lambda i, j: i == j, (3, 3), dtype=int)
    print('Array of bool. diagonaly true. False elsewhere: \n', arr, '\n')

    arr = np.fromfunction(lambda x, y: x + y, (2, 2), dtype=int)
    print('another array [lambda x, y: x + y] : \n', arr, '\n')

    arr = np.fromfunction(f_2d, (4, 4), dtype=float)
    print('another array [f_2d]: \n', arr, '\n')

    arr = np.fromfunction(f_1d, (5,), dtype=float)
    print('another array [f_1d]: \n', arr, '\n')


@func_name_printer
def np_fromiter():
    """
    using numpy.fromiter(iterable, dtype, count=-1)
          Create a new 1-dimensional array from an iterable object.

    note : Specify count to improve performance. It allows fromiter to
           pre-allocate the output array, instead of resizing it on demand.

    :return: None
    """

    iterable = (x**2 for x in range(10))  # generator
    print('init iterable object : ', iterable, '\n')
    arr = np.fromiter(iterable, dtype=int, count=10)
    print('constructed array : \n', arr, '\n')


@func_name_printer
def np_fromstring():
    """
    using numpy.fromstring(string, dtype=float, count=-1, sep='')
          A new 1-D array initialized from text data in a string.

    :return: None
    """

    string = '1 2 3 4'
    arr = np.fromstring(string, dtype=int, sep=' ')
    print('init string : ', string)
    print('read array  : ', arr, '\n')

    string = string.replace(' ', ', ')
    arr = np.fromstring(string, dtype=int, sep=',')
    print('init string : ', string)
    print('read array  : ', arr, '\n')


@func_name_printer
def np_loadtxt():
    """
    using numpy.loadtxt(fname, dtype=<class 'float'>, comments='#',
                        delimiter=None, converters=None, skiprows=0,
                        usecols=None, unpack=False, ndmin=0, encoding='bytes')

          Load data from a text file. Each row in the text file must have the
          same number of values.

    :return: None
    """

    string = u'0 1\n 2 3'
    c = StringIO(string)  # unicode string
    arr = np.loadtxt(c)
    print('content of file :\n', string)
    print('read array : \n', arr, '\n')

    string = u'M 21 72\n F 35 58'
    c = StringIO(string)
    custom_type = {'names': ('gender', 'age', 'weight'),
                   'formats': ('S1', int, float)}
    arr = np.loadtxt(c, dtype=custom_type)
    print('input string : \n', string)
    print('read array : \n', arr, '\n',
          'first row gender : ', arr['gender'][0], '\n')

    string = u'1, 0, 2\n3, 0, 4\n10, 11, 12'
    c = StringIO(string)
    arr = np.loadtxt(c, delimiter=',')

    # since StringIO is a file-like object, reading it will make the
    # filepointer points to EOF. Going back to beginning of file
    c.seek(0)

    x, y = np.loadtxt(c, delimiter=',', usecols=(0, 2), unpack=True)
    print('init string : \n', string)
    print('full array : \n', arr, '\n')
    print('read into two arrays : \n',
          'column idx 0', x, '\n', 'column idx 2', y, '\n')


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
    np_asanyarray()
    np_ascontinuousarray()
    np_copy()
    np_frombuffer()
    np_fromfile()
    np_fromfunction()
    np_fromiter()
    np_fromstring()
    np_loadtxt()


if __name__ == '__main__':
    main()
