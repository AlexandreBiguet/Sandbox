"""
indexing, slicing, iterating
"""

import numpy as np


def one_dim():
    arr = np.arange(10)**2
    print('arr = ', arr)
    print('arr[4] = ', arr[4])
    print('arr[2::2] = ', arr[2::2])

    arr[2] = -4
    print('arr = ', arr)

    rev_arr = arr[::-1]
    print('rev arr : ', rev_arr)

    count = 0
    for elem in arr:
        print('arr[', count, '] = ', elem)
        count += 1

    def func(x):
        print('x_i = ', x)
        positive_indexes = x > 0
        print('indexes = ', positive_indexes)
        x = np.log(x[positive_indexes])
        print('x_f = ', x)
        return x

    arr2 = np.fromfunction(func, (10,), dtype=int)
    print('\n', 'from function arr = ', arr2)


def two_dim():
    def fun2(x, y):
        return 2*x + y

    dim = 5
    arr = np.fromfunction(fun2, (dim, dim), dtype=int)
    print('\nfrom func 2d\narr =\n', arr)
    print('\narr[0, 0] should be 0 : ', arr[0, 0])
    print('arr[3, 1] should be 7 : ', arr[3, 1])

    first_row = arr[0, 0:dim]
    second_row = arr[1, 0:dim]
    print('1st row : ', first_row)
    print('2nd row : ', second_row)

    first_col = arr[0:dim, 0]
    second_col = arr[0:dim, 1]
    print('1st col : ', first_col)
    print('2nd col : ', second_col)

    last_two_rows = arr[dim-2:dim, 0:dim]
    print('last two rows :\n', last_two_rows)

    last_two_cols = arr[0:dim, dim-2:dim]
    print('last two cols :\n', last_two_cols)


def multidim_dots():
    arr = np.arange(20).reshape(2, 2, 5)
    print('\narr : \n', arr, '\nshape : ', arr.shape)

    first_dim_tab = arr[0, ...]
    print('\n first dim tab :\n', first_dim_tab)

    last_dim_tab = arr[-1, ...]
    print('\n last dim tab: \n', last_dim_tab)

    first_col_two_dim = arr[..., 0]
    print('\n first col two dim: \n', first_col_two_dim)

    flattened_first_col_two_dim = np.ravel(first_col_two_dim)
    print('\n first col two dim (flattened): \n',
          flattened_first_col_two_dim, '\n')

    # iterating over first axis of array
    count = 0
    for tab in arr:
        if count > 0:
            print('')
        print('tab [{}] = \n{}\n'.format(count, tab))
        # iterating over the rows of the current tab
        for row in tab:
            print(' -- row : ', row)
        count += 1

    # iterating over each element:
    print('ndim  : ', arr.ndim)
    print('shape : ', arr.shape)
    for element in arr.flat:
        print(element, end=' ')


def main():
    one_dim()
    two_dim()
    multidim_dots()


if __name__ == '__main__':
    main()
