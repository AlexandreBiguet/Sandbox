"""
shape manipulation
"""

import numpy as np


def changing_shape():
    arr = np.arange(-5, 5)
    print('\n\ninitial array :\n', arr, '\nwith shape: ', arr.shape, '\n')

    shape = (2, 5)
    new_shape = (5, 2)

    reshaped_arr = arr.reshape(shape)

    print('reshaped to ', shape, ': \n', reshaped_arr, '\n')

    arr.resize(shape)
    print('resized to ', shape, ': \n', arr, '\n')

    arr.resize(new_shape)
    print('resized to ', new_shape, ': \n', arr, '\n')

    arr_transposed = arr.transpose()
    print('transposed resized array : \n', arr_transposed, '\n')

    reshaped_arr_transposed = reshaped_arr.transpose()
    print('transposed reshaped array: \n', reshaped_arr_transposed)


def stacking_arrays():
    a1 = np.arange(10, 30).reshape(2, 10)
    a2 = np.arange(10)
    a3 = np.arange(-10,0)
    a4 = np.linspace(0.0, 1.0, num=10, dtype=int)

    print('\na1 : \n', a1, '\n')
    print('a2 : \n', a2, '\n')
    print('a3 : \n', a3, '\n')
    print('a4 : \n', a4, '\n')

    vstacked = np.vstack((a1, a2, a3, a4))
    print('\nvstack((a1, a2, a3, a4)) : \n', vstacked)

    hstacked = np.hstack((a2, a3, a4))
    print('\nhstack((a2, a3, a4)) : \n', hstacked)


def main():
    changing_shape()
    stacking_arrays()


if __name__ == '__main__':
    main()
