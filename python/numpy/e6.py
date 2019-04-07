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

    ar1 = np.array([1, 2])
    ar2 = np.array([3, 4])
    ar3 = np.array([5, 6])
    col_stacked = np.column_stack((ar1, ar2, ar3))
    print('\nar1 = ', ar1)
    print('ar2 = ', ar2)
    print('ar3 = ', ar3)
    print('column_stack((ar1, ar2, ar3)) = \n', col_stacked, '\n')

    print('creating array using r_: \n')
    arr = np.r_[1:10, 3:6, 1, 2]
    print('np.r_[1:10, 3:6, 1, 2] = \n', arr, '\n')

    print('creating array using c_: \n')
    arr = np.c_[1:10, 3:12]
    print('np.c_[1:10, 3:12] : \n', arr, '\n')


def splitting_arrays():
    ar = np.floor(5.0 * np.random.random((2, 4)))
    print('random array : \n', ar, '\n')

    hsplitted = np.hsplit(ar, 2)
    print('hsplitted = \n', hsplitted, '\n')
    print('iter over array list : \n')
    for arr in hsplitted:
        print(arr, '\n')


def main():
    changing_shape()
    stacking_arrays()
    splitting_arrays()


if __name__ == '__main__':
    main()
