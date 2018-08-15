"""
from
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_gui/py_image_display/py_image_display.html

reading and writing an image using matplotlib

Note : opencv uses BGR but matplotlib uses RGB

"""

import sys
import cv2
from matplotlib import pyplot as plt


def main():

    if len(sys.argv) < 2:
        print('one positional arg. required : path to an image')
        quit()

    img = cv2.imread(sys.argv[1])
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

    plt.subplot(2, 1, 1)
    plt.gca().set_title('bgr showed by matplotlib')
    plt.imshow(img)

    plt.subplot(2, 1, 2)
    plt.gca().set_title('rgb showed by matplotlib')
    plt.imshow(img_rgb)
    plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)

    plt.show()


if __name__ == '__main__':
    main()
