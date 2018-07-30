//
//  ex8.cpp
//  opencv-samples
//
//  Created by Alexandre Biguet on 28/07/2018 at 12:09.
//

/**
 * Using together dowsampling and canny edge detector
 */

#include <iostream>

#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {

  if (argc < 2) {
    std::cout << "First argument must be a valid path to an image \n";
    return -1;
  }

  // 1- get the input image

  cv::Mat input = cv::imread(argv[1]);

  // 2- transform input image to grayscale

  cv::Mat igray;
  cv::cvtColor(input, igray, cv::COLOR_BGR2GRAY);

  // 3- downsampling grayscale image n times

  uint ndown = 2;
  cv::Mat tmp, down;
  cv::pyrDown(igray, down);
  while (ndown != 1) {
    down.copyTo(tmp);
    cv::pyrDown(tmp, down);
    --ndown;
  }

  // 4- canny edge detection on the downsample image

  double threshold1 = 10.0;
  double threshold2 = 100.0;
  int apertureSize = 3;
  bool L2gradient = false;

  // See example-2-7.cpp for the meaning of the canny edge detector algo
  // parameters

  cv::Mat canny;
  cv::Canny(down, canny, threshold1, threshold2, apertureSize, L2gradient);

  // -End- outputs images

  cv::namedWindow("input"); // WINDOW_AUTOSIZE is the default
  cv::namedWindow("gray");
  cv::namedWindow("downsampled");
  cv::namedWindow("canny");

  cv::imshow("input", input);
  cv::imshow("gray", igray);
  cv::imshow("dowsampled", down);
  cv::imshow("canny", canny);

  cv::waitKey(0);

  return 0;
}

// example-2-8.cpp ends here