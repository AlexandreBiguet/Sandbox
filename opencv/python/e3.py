"""
from
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_gui/py_video_display/py_video_display.html

capturing video from camera

displaying original and gray
"""

import cv2


def main():
    video_cap = cv2.VideoCapture(0)

    while True:

        # Capture frame-by-frame
        ret, frame = video_cap.read()

        # displaying the original
        cv2.imshow('original', frame)

        # Our operations on the frame come here
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Display the resulting frame
        cv2.imshow('gray', gray)

        if cv2.waitKey(40) == ord('q'):
            break

    # When everything done, release the capture
    video_cap.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
