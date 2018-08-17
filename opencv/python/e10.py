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

    top = 10
    bottom = 10
    left = 10
    right = 10

    replicate = cv2.copyMakeBorder(source, top, bottom, left, right,
                                   cv2.BORDER_REPLICATE,)

    plt.subplot(221)
    plt.imshow(source, 'gray'), plt.title('original')

    plt.subplot(222)
    plt.imshow(replicate, 'gray'), plt.title('replicate')

    plt.show()


if __name__ == '__main__':
    main()

