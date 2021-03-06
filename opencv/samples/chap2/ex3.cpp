//
//  ex3.cpp
//  opencv-samples
//
//  Created by Alexandre Biguet

#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 * The current program allows the user to play a video and select (as an
 * optional second argument) the framerate use to display the video
 */

void help() {
  std::cout << "first argument must be a valid path to a video \n";
  std::cout << "second argument (optional) the framerate (default to 40 ms) \n";
}

int main(int argc, char** argv) {
  if (argc < 2) {
    help();
    return -1;
  }

  std::size_t stupid_framerate_ms(40);

  if (argc >= 2) {
    stupid_framerate_ms = std::stoul(argv[2]);
  }

  cv::namedWindow("title", cv::WINDOW_AUTOSIZE);
  cv::VideoCapture capture;
  capture.open(std::string(argv[1]));
  cv::Mat frame;

  std::cout << "video path : " << argv[1] << "\n";
  std::cout << "framerate  : " << stupid_framerate_ms << "\n";

  for (;;) {
    capture >> frame;
    if (frame.empty()) {
      std::cout << "frame is empty (end of video)\n";
      break;
    }

    cv::imshow("title", frame);
    if (cv::waitKey((int) stupid_framerate_ms) >= 0) {
      break;
    }
  }

  cv::destroyWindow("title");

  return 0;
}
