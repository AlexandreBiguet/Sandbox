"""
Core operations

from
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_core/py_basic_ops/py_basic_ops.html#basic-ops

making borders for images (padding)
"""

import cv2
import numpy as np
from matplotlib import pyplot as plt


img_path = '../data/photo.jpg'


def main():
    source = cv2.imread(img_path, cv2.IMREAD_COLOR)
    source = cv2.cvtColor(source, cv2.COLOR_BGR2RGB)

    lenght = 100
    top = lenght
    bottom = lenght
    left = lenght
    right = lenght

    border_type_list = (i for i in dir(cv2) if 'BORDER' in i)
    print('List of border type : ')
    for btype in border_type_list:
        print(btype)

    constant = cv2.copyMakeBorder(source, top, bottom, left, right,
                                  cv2.BORDER_CONSTANT)

    default = cv2.copyMakeBorder(source, top, bottom, left, right,
                                 cv2.BORDER_DEFAULT)

    isolated = cv2.copyMakeBorder(source, top, bottom, left, right,
                                  cv2.BORDER_ISOLATED)

    reflect = cv2.copyMakeBorder(source, top, bottom, left, right,
                                 cv2.BORDER_REFLECT)

    reflect101 = cv2.copyMakeBorder(source, top, bottom, left, right,
                                    cv2.BORDER_REFLECT101)

    reflect_101 = cv2.copyMakeBorder(source, top, bottom, left, right,
                                     cv2.BORDER_REFLECT_101)

    replicate = cv2.copyMakeBorder(source, top, bottom, left, right,
                                   cv2.BORDER_REPLICATE)

    wrap = cv2.copyMakeBorder(source, top, bottom, left, right,
                              cv2.BORDER_WRAP)

    # pyplot imshow options
    options = {'cmap': 'gray', 'aspect': 'equal'}

    # Fig. 1

    plt.figure()
    plt.imshow(source, **options)
    plt.title('original')

    # Fig. 2

    plt.figure()
    plt.subplot(131)
    plt.imshow(constant, **options)
    plt.title('constant')

    plt.subplot(132)
    plt.imshow(default, **options)
    plt.title('default')

    plt.subplot(133)
    plt.imshow(isolated, **options)
    plt.title('isolated')

    # Fig. 3

    plt.figure()
    plt.subplot(131)
    plt.imshow(reflect, **options)
    plt.title('reflect')

    plt.subplot(132)
    plt.imshow(reflect101, **options)
    plt.title('reflect101')

    plt.subplot(133)
    plt.imshow(reflect_101, **options)
    plt.title('reflect_101')

    # Fig. 4

    plt.figure()
    plt.subplot(121)
    plt.imshow(replicate, **options)
    plt.title('replicate')

    plt.subplot(122)
    plt.imshow(wrap, **options)
    plt.title('wrap')

    # Plot

    plt.show()


if __name__ == '__main__':
    main()

