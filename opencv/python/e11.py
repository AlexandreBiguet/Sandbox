"""
Arithmetic Operations on Images

From
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_core/py_image_arithmetics/py_image_arithmetics.html

Image addition
"""

import cv2
import numpy as np

# 3 paths to images
paths = ['../data/photo.jpg',
         '../data/photo2.jpg',
         '../data/photo3.jpg']


def getpath():
    for p in paths:
        yield p


def addition(callable_add, add_suffix):
    """
    Performs the addition of several images and imshow them

    :param callable_add: a callable that takes two numpy array and add them

    :param add_suffix: a string corresponding to the package used for the
                       addition operation

    :return: None
    """

    imgs = []

    for p in paths:
        imgs.append(cv2.imread(p, cv2.IMREAD_COLOR))

    path_iter = getpath()

    for img in imgs:
        cv2.imshow(next(path_iter), img)

    added = []
    added_names = ['add_%s (%s, %s)' % (add_suffix, paths[0], paths[1]),
                   'add_%s (%s, %s)' % (add_suffix, paths[0], paths[2])]

    added.append(callable_add(imgs[0], imgs[1]))
    added.append(callable_add(imgs[0], imgs[2]))

    added_names_iter = (i for i in range(len(added_names)))

    for adds in added:
        cv2.imshow(added_names[next(added_names_iter)], adds)

    cv2.waitKey()
    cv2.destroyAllWindows()


def main():
    addition(cv2.add, 'opencv')
    addition(np.add, 'numpy')


if __name__ == '__main__':
    main()
