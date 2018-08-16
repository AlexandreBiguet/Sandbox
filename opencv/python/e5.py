"""
drawing tools in opencv

from https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_gui/py_drawing_functions/py_drawing_functions.html
"""

import numpy as np
import cv2


def main():

    # creating a black image
    img = np.zeros((512, 512, 3), np.uint8)

    # drawing a blue line with thickness of 5 px. From top left corner to
    # bottom right corner
    cv2.line(img, (0, 0), (511, 511), (255, 0, 0), 5)

    cv2.rectangle(img, (384, 0), (510, 128), (0, 255, 0), 3)
    cv2.circle(img, (447, 63), 63, (0, 0, 255), -1)
    cv2.ellipse(img, (256, 256), (100, 50), 0, 0, 180, 255, -1)

    pts = np.array([[10, 5], [20, 30], [70, 20], [50, 10]],
                   dtype=np.int32).reshape((-1, 1, 2))

    cv2.polylines(img, [pts], True, (0, 255, 255))

    cv2.imshow('drawing', img)
    cv2.waitKey()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
