"""
Core operations

from
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_core/py_basic_ops/py_basic_ops.html#basic-ops

Splitting and merging image channel
"""

import cv2
import numpy as np


img_path = '../data/photo.jpg'


def main():
    img = cv2.imread(img_path, 1)

    # b, g, r = cv2.split(img)

    b = img[:, :, 0]
    g = img[:, :, 1]
    r = img[:, :, 2]

    b_chnl = np.array(b, dtype=np.uint8)
    g_chnl = np.array(g, dtype=np.uint8)
    r_chnl = np.array(r, dtype=np.uint8)

    cv2.imshow('original', img)
    cv2.imshow('blue channel', b_chnl)
    cv2.imshow('green channel', g_chnl)
    cv2.imshow('red channel', r_chnl)

    cv2.waitKey()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
