//
//  ex6.cpp
//  opencv-samples
//
//  Created by Alexandre Biguet on 28/07/2018 at 11:23.
//

/**
 * Aim : downsample an image by a factor of 2 using the gaussian blurring.
 *
 * If an image is downsampled several times, a 'scale space', also known as
 * 'image pyramid', is formed.
 *
 * This technique is used to handle the changing scales in which a scene or
 * object is observed
 */

/**
 * keywords:
 * Nyquist-Shannon sampling theorem
 * dirac delta convolution introduces high-frequency in the output signal
 * (limited by a high-pass filter)
 *
 * TODO : check the implementation of cv::pyrDown, cv::pyrUp
 *
 */

#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {

  if (argc < 2) {
    std::cout << "First argument must be a valid path to an image \n";
    return -1;
  }

  cv::Mat original, modified_down, modified_up, back;

  // original is the read photo from input
  // modified_down is downsample output of original
  // modified_up is upsample output of original
  // back is upsample of downsample of original

  // -> back != original as expected

  cv::namedWindow("original", cv::WINDOW_NORMAL);
  cv::namedWindow("modified-down", cv::WINDOW_NORMAL);
  cv::namedWindow("modified-up", cv::WINDOW_NORMAL);
  cv::namedWindow("down-and-up", cv::WINDOW_NORMAL);

  original = cv::imread(argv[1]);
  cv::imshow("original", original);

  cv::pyrDown(original, modified_down);

  cv::imshow("modified-down", modified_down);

  cv::pyrUp(original, modified_up);
  cv::imshow("modified-up", modified_up);

  cv::pyrUp(modified_down, back);
  cv::imshow("down-and-up", back);

  cv::waitKey(0);

  return 0;
}


// example-2-6.cpp ends here