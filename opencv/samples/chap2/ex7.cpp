//
//  ex7.cpp
//  opencv-samples
//
//  Created by Alexandre Biguet on 28/07/2018 at 11:42.
//

/**
 * Canny Edge detector
 *
 * the canny edge detector outputs an image which has the same size as the input
 * image but is single-channel.
 */

// TODO : check how to write an image to file with opencv and look at the Canny
//        algo parameters effects on output

#include <iostream>

#include <opencv2/opencv.hpp>

int main(int argc, char ** argv) {

  if (argc < 2) {
    std::cout << "first argument should be a valid path to an image \n";
    return -1;
  }

  cv::Mat input, gray, canny, canny_from_input;

  // input is the original image
  // gray is the grayscale converted input image
  // canny is the edge detected from gray image.
  // -> since the output of the canny edge detector is single channel, the
  // input image can be first converted to gray before being Canny-ized
  // Q : what happens if we canny the original image directly ?
  // A : The doc says the input should be a 8-bit image. But it seems that
  //     there is no difference.. TODO : to be investigated

  cv::namedWindow("input", cv::WINDOW_NORMAL);
  cv::namedWindow("grayscale", cv::WINDOW_NORMAL);
  cv::namedWindow("canny-from-gray", cv::WINDOW_NORMAL);
  cv::namedWindow("canny-from-input", cv::WINDOW_NORMAL);

  input = cv::imread(argv[1]);

  cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
  cv::imshow("grayscale", gray);

  double threshold1 = 10.0;
  double threshold2 = 100.0;
  int apertureSize = 3;
  bool L2gradient = false;

  // threshold1 is the first threshold for the hysteresis procedure
  // threshold2 is the second threshold for the hysteresis procedure
  // apertureSize : aperture size for the Sobel Operator
  // L2gradient : if true the L2-norm is used else the L1-norm is used to
  //              compute the image gradient.

  cv::Canny(gray, canny, threshold1, threshold2, apertureSize, L2gradient);
  cv::imshow("canny-from-gray", canny);

  cv::Canny(input, canny_from_input, threshold1, threshold2,
      apertureSize, L2gradient);
  cv::imshow("canny-from-input", canny);

  cv::waitKey(0);

  return 0;
}

// example-2-7.cpp ends here