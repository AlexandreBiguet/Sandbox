//
//  waitkey.cpp 
//  opencv-samples
//
//  Created by Alexandre Biguet on 26/07/2018 at 13:14.
//
#include <iostream>

#include <opencv2/highgui/highgui.hpp>

// https://stackoverflow.com/questions/5217519/what-does-opencvs-cvwaitkey-function-do
// cvWaitKey(x) / cv::waitKey(x) does two things:

// It waits for x milliseconds for a key press on a OpenCV window (i.e. created
// from cv::imshow()). Note that it does not listen on stdin for console input.
// If a key was pressed during that time, it returns the key's ASCII code.
// Otherwise, it returns -1. (If x is zero, it waits indefinitely for the
// key press.)
//
// It handles any windowing events, such as creating windows with
// cv::namedWindow(), or showing images with cv::imshow().
//
// A common mistake for opencv newcomers is to call cv::imshow() in a loop
// through video frames, without following up each draw with cv::waitKey(30).
// In this case, nothing appears on screen, because highgui is never given time
// to process the draw requests from cv::imshow().

int main() {

  cv::Mat frame(100, 100, CV_8UC1);

  cv::namedWindow("window title", cv::WINDOW_AUTOSIZE);

  while (true) {

    cv::imshow("window title", frame);

    // wait for a key press when the 'running application' is fg. returns the
    // pressed key

    auto c = cv::waitKey(300);

    if ( c == 'k') {
      break;
    }

    std::cout << "key : [" << c << "] \n";

  }

  return 0;
}

// waitkey.cpp ends here