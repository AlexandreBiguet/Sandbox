"""
from
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_gui/py_video_display/py_video_display.html

displaying video from file
"""

import cv2


video_path = '../data/video.mov'


def main():

    video_capture = cv2.VideoCapture(video_path)

    while video_capture.isOpened():
        
        ret, frame = video_capture.read()

        if not ret:
            break

        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        cv2.imshow('rgb', frame)

        if cv2.waitKey(40) == ord('q'):
            break

    cv2.destroyWindow('rgb')
    video_capture.release()


if __name__ == '__main__':
    main()
