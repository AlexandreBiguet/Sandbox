"""
Arithmetic Operations on Images

From
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_core/py_image_arithmetics/py_image_arithmetics.html

Image blending
"""

import cv2
import numpy as np


paths = ['../data/photo2.jpg',
         '../data/photo3.jpg']


def blend(img1, img2, weights):
    """
    blends the two input images using the inputs weights

    :param img1: a numpy array

    :param img2: another numpy array

    :param weights: (alpha, beta, gamma)

    :return: a numpy array so that out = alpha * img1 + beta * img2 + gamma
    """

    return cv2.addWeighted(src1=img1, alpha=weights[0],
                           src2=img2, beta=weights[1], gamma=weights[2])


def simple_blend(input_paths, output_path,
                 weights=[0.7, 0.3, 0.0], show_output=False):
    """
    Simple blending of images from the input path list, written
    into the output path

    :param input_paths: 2-element list of input path of images to be blended

    :param output_path:

    :param weights : a 3-element list of weights (alpha, beta, gamma)

    :return: None
    """

    if len(input_paths) > 2:
        print('input paths length must be 2 ')
        return None

    imgs = []

    for p in input_paths:
        imgs.append(cv2.imread(p, cv2.IMREAD_COLOR))

    out = blend(imgs[0], imgs[1], weights)

    if show_output:

        cv2.imshow('output = %s w:[%f] + %s w:[%f] + %f'
                   % (input_paths[0], weights[0], input_paths[1],
                      weights[1],  weights[2]), out)

        cv2.waitKey()
        cv2.destroyAllWindows()

    cv2.imwrite(output_path, out)


def main():

    simple_blend(paths, '../data/e12_output.jpg', show_output=True)


if __name__ == '__main__':
    main()
