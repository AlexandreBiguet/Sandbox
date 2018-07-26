//
//  example-2-4.cpp 
//  opencv-samples
//
//  Created by Alexandre Biguet on 26/07/2018 at 12:16.
//

#include <iostream>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int slider_position = 0;
int run = 0;
int single_step = 0;
cv::VideoCapture capture; /* NOLINT */

void onTrackbarSlide_cb(int pos, void *) {
  capture.set(cv::CAP_PROP_POS_FRAMES, pos);
  if (! single_step){
    run = 1;
  }
  single_step = 0;
}

void help() {
  std::cout << "First argument must be a path to a valid video \n";
}

int main(int argc, char ** argv) {

  if (argc < 2) {
    help();
    return -1;
  }

  auto video_path = std::string(argv[1]);
  std::string w_title("title");
  std::string trackbar_name ("position");

  capture.open(video_path);
  auto frame_nb = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_COUNT));
  auto frame_width = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
  auto frame_height = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));
  std::cout << "Video : " << video_path << "\n";
  std::cout << "  - number of frames : " << frame_nb << "\n"
            << "  - (widht, height)  : (" << frame_width
            << " ; " << frame_height << ") \n";

  cv::namedWindow(w_title, cv::WINDOW_AUTOSIZE);

  cv::createTrackbar(
      trackbar_name, w_title,
      &slider_position, frame_nb, onTrackbarSlide_cb);

  cv::Mat current_frame;

  for(;;) {

    if (run != 0) {

      capture >> current_frame;

      if (current_frame.empty()) {
        break;
      }

      auto cur_pos = static_cast<int> (capture.get(CV_CAP_PROP_POS_FRAMES));
      single_step = 1;
      cv::setTrackbarPos(trackbar_name, w_title, cur_pos);
      cv::imshow(w_title, current_frame);

      run -= 1;
    }

    auto c = static_cast<char> (cv::waitKey(10));
    if (c == 's') {
      run = 1;
      std::cout << "Single step, [run : " << run << "] \n";
    }

    if (c == 'r') {
      run = -1;
      std::cout << "Run mode, [run : " << run << "] \n";
    }

    if (c == 27) {
      break;
    }
  }

  return 0;
}

// example-2-4.cpp ends here