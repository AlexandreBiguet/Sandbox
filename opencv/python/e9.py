"""
Core operations

from
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_core/py_basic_ops/py_basic_ops.html#basic-ops

Splitting and merging image channel
"""

import cv2
import numpy as np


img_path = '../data/photo.jpg'


def using_split():
    img = cv2.imread(img_path, cv2.IMREAD_COLOR)
    b, g, r = cv2.split(img)
    blue = cv2.merge((b, np.zeros_like(g), np.zeros_like(r)))
    red = cv2.merge((np.zeros_like(b), np.zeros_like(g), r))
    green = cv2.merge((np.zeros_like(b), g, np.zeros_like(r)))
    cv2.imshow('original', img)
    cv2.imshow('blue channel', blue)
    cv2.imshow('red channel', red)
    cv2.imshow('green channel', green)

    cv2.waitKey()
    cv2.destroyAllWindows()


def only_blue():
    img = cv2.imread(img_path, cv2.IMREAD_COLOR)

    img_cpy = np.copy(img)

    img_cpy[:, :, 1] = 0
    img_cpy[:, :, 2] = 0

    cv2.imshow('original', img)
    cv2.imshow('blue channel', img_cpy)

    cv2.waitKey()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    only_blue()
    using_split()
