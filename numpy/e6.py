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


def main():
    changing_shape()


if __name__ == '__main__':
    main()
