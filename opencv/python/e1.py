"""
from
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_gui/py_image_display/py_image_display.html

reading and writing an image using opencv

"""

import sys
import cv2


def main():

    if len(sys.argv) < 2:
        print('one positional argument is required : a path to an image')
        quit()

    file_name = sys.argv[1]
    print('file name : ', file_name)

    img = cv2.imread(file_name)
    cv2.imshow('window name', img)

    key = cv2.waitKey(0)

    if key == ord('s'):
        print('writing to new image file')
        img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        cv2.imwrite('../data/e1_output.jpg', img_gray)

    cv2.destroyWindow('window name')


if __name__ == '__main__':
    main()
