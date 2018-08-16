"""
core operations

from
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_core/py_basic_ops/py_basic_ops.html#basic-ops

selecting a region of interest (ROI) and duplicate it on the same image
"""

import numpy as np
import cv2
from matplotlib import pyplot as plt

img_path = '../data/photo.jpg'


def tuto_roi():

    img = cv2.imread(img_path)

    # selecting a region of the input image
    bottom_right = (531, 404)
    top_left = (450, 352)

    roi = img[352:404, 450:531]
    dy = 531-450
    dx = 404-352

    # drawing a rectangle
    cv2.rectangle(img, top_left, bottom_right, color=(0, 0, 0), thickness=2)

    img[200:200 + dx, 200:200 + dy] = roi

    # show image using matplotlib
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    plt.imshow(img)
    plt.show()


def main():
    tuto_roi()


if __name__ == '__main__':
    main()
