"""
numpy array printing

see np.set_printoptions for np.array print options
"""

import numpy as np


def print_array(array):
    print('[dim : {}] \n {} \n\n'.format(array.ndim, array))


def main():
    one_dim = np.arange(3)
    two_dim = np.arange(6).reshape(2, 3)
    three_dim = np.arange(36).reshape((2, 3, 6))
    print_array(one_dim)
    print_array(two_dim)
    print_array(three_dim)

    large_array = np.arange(1000)
    print_array(large_array)

    np.set_printoptions(threshold=100)

    large_array = np.arange(101)
    print_array(large_array)


if __name__ == '__main__':
    main()