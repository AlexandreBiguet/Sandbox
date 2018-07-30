//
//  ex4.cpp
//  opencv-samples
//
//  Created by Alexandre Biguet on 26/07/2018 at 12:16.
//

#include <iostream>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 * The current program displays a video allows the user to
 *  - move in the video using a trackbar
 *  - play a single frame
 *  - play the video
 *  - play 10 frames
 */

int slider_position = 0;

/// a negative value for run means the video is in continuous video mode
/// a positive value indicates the number of frame to be displayed before
/// stopping
int run = 0;

/// allows to set the trackbar position even if the user did not click on the
/// trackbar. This variable is set to true when called from the main program.
/// sets to false when the user clicked on the trackbar
bool trackbar_main_mode = false;

cv::VideoCapture capture; /* NOLINT */

void onTrackbarSlide_cb(int pos, void *) {
  capture.set(cv::CAP_PROP_POS_FRAMES, pos);
  if (! trackbar_main_mode){
    run = 1;
  }
  trackbar_main_mode = false;
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

  auto frame_nb     = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_COUNT));
  auto frame_width  = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
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

    auto c = static_cast<char> (cv::waitKey(10));

    if (run != 0) {

      capture >> current_frame;

      if (current_frame.empty() || c == 'k') {
        break;
      }

      auto cur_pos = static_cast<int> (capture.get(CV_CAP_PROP_POS_FRAMES));
      trackbar_main_mode = true;
      cv::setTrackbarPos(trackbar_name, w_title, cur_pos);
      cv::imshow(w_title, current_frame);

      run -= 1;
    }

    if (c == 's') {
      run = 1;
      std::cout << "Single step, [run : " << run << "] \n";
    }

    if (c == 'r') {
      run = -1;
      std::cout << "Run mode, [run : " << run << "] \n";
    }

    if (c == 'm') {
      run = 10;
      std::cout << "multi-step (10 frames), [run : " << run << "] \n";
    }

  }

  cv::destroyWindow(w_title);

  return 0;
}

// example-2-4.cpp ends here