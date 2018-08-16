"""
core operations

from
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_core/py_basic_ops/py_basic_ops.html#basic-ops

modifying an image. Drawing an horizontal line on image
"""

import numpy as np
import cv2

img_path = '../data/photo.jpg'
show_image = True


def image_properties():

    img = cv2.imread(img_path)

    print('BGR at (10, 10) : ', img[10, 10])
    print('image type : ', type(img))
    print('image dtype : ', img.dtype)
    print('image shape : ', img.shape)

    if show_image:

        # modified image is a deep copy of img. Its 10th rows is black
        modified = np.copy(img)
        modified[10, :] = [0, 0, 0]

        cv2.imshow('original', img)
        cv2.imshow('modified', modified)
        cv2.waitKey()
        cv2.destroyAllWindows()


def main():
    image_properties()


if __name__ == '__main__':
    main()
