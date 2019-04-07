"""
- np.array creation
- np.zeros : creation of an array filled with 0
- np.ones  : creation of an array filled with 1
- np.empty : creation of an uninitialized array

- np.ndarray.shape : returns a tuple of array dimensions.

The rank of a tensor is given by the number of element of its shape property
TODO : check if this is what is returned by ndarray.ndim

"""

import numpy as np


def print_array_info(array):
    print('\n', array)
    print(' - type  : ', array.dtype)
    print(' - ndim  : ', array.ndim)
    print(' - shape : ', array.shape)
    print(' - rank  : ', len(array.shape))


def main():
    a = np.array([1, 2, 4])
    print_array_info(a)

    a = np.array([1.0, 2.0, 4.0])
    print_array_info(a)

    a = np.array([1.0 + 2.j, 3.0 + 4.j])
    print_array_info(a)

    a = np.array([(1, 2), (3, 4)], ndmin=3)
    print_array_info(a)

    s = (2, 3)
    z = np.zeros(shape=s)
    print_array_info(z)

    s = 3
    o = np.ones(shape=s)
    print_array_info(o)

    s = (3, 3, 3)
    e = np.empty(s)
    print_array_info(e)


if __name__ == '__main__':
    main()
