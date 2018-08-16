"""
from
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_gui/py_video_display/py_video_display.html

displaying video from file and writing it to another file
"""

import cv2


video_path = '../data/video.mov'
output_path = '../data/video_output_e4.avi'


def main():

    video_capture = cv2.VideoCapture(video_path)

    fourcc = cv2.VideoWriter_fourcc(*'MJPG')
    frame_width = int(video_capture.get(3))
    frame_height = int(video_capture.get(4))
    video_writer = cv2.VideoWriter(output_path, fourcc, 20.0,
                                   (frame_width, frame_height))

    while video_capture.isOpened():

        ret, frame = video_capture.read()

        if not ret:
            break

        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        cv2.imshow('rgb', frame)

        video_writer.write(frame)

        if cv2.waitKey(40) == ord('q'):
            break

    cv2.destroyWindow('rgb')
    video_capture.release()


if __name__ == '__main__':
    main()
