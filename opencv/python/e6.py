"""
mouse as a paint brush
simple demo

from https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_gui/py_mouse_handling/py_mouse_handling.html
"""

import numpy as np
import cv2


def main():
    events = [i for i in dir(cv2) if 'EVENT' in i]

    # mouse callback function
    def draw_circle(event, x, y, flags, param):
        if event == cv2.EVENT_LBUTTONDBLCLK:
            cv2.circle(img, (x, y), 100, (255, 0, 0), -1)

    # Create a black image, a window and bind the function to window
    img = np.zeros((512, 512, 3), np.uint8)

    cv2.namedWindow('image')

    cv2.setMouseCallback('image', draw_circle)

    while True:
        cv2.imshow('image', img)

        if cv2.waitKey(40) & 0xFF == 27:  # ESC key
            break

    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
