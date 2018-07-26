//
//  example-2-5.cpp 
//  opencv-samples
//
//  Created by Alexandre Biguet on 26/07/2018 at 20:19.
//

/**
 * This programs allows the user to play a video and to apply a simple
 * operation on each frame of the video
 */

#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// TODO 1 : check the implementation of the gaussian blur
// TODO 2 : add several blurring types (choice from command line)

int main(int argc, char** argv) {

  if (argc < 2) {
    std::cout << "first argument must be a valid path to a video file \n";
    return -1;
  }

  auto video_path = std::string(argv[1]);

  std::string original_w_title("original");
  std::string modified_w_title("modified");
  cv::VideoCapture capture;
  capture.open(video_path);

  cv::namedWindow(original_w_title, cv::WINDOW_NORMAL);
  cv::namedWindow(modified_w_title, cv::WINDOW_NORMAL);

  cv::Mat frame, modif;

  for (;;) {
    capture >> frame;

    auto c = static_cast<char> (cv::waitKey(10));

    if (c == 'k' || frame.empty()) {
      break;
    }

    cv::imshow(original_w_title, frame);

    // from the doc.

    // ksize Gaussian kernel size. ksize.width and ksize.height can differ but
    // they both must be positive and odd. Or, they can be zero's and then they
    // are computed from sigma.

    // sigmaX Gaussian kernel standard deviation in X direction.

    // sigmaY Gaussian kernel standard deviation in Y direction;
    // if sigmaY is zero, it is set to be equal to sigmaX, if both sigmas are
    // zeros, they are computed from ksize.width and ksize.height, respectively
    // (see #getGaussianKernel for details); to fully control the result
    // regardless of possible future modifications of all this semantics, it
    // is recommended to specify all of ksize, sigmaX, and sigmaY.

    cv::Size kernelSize(5, 5);
    double sigma = 3.0;

    cv::GaussianBlur(frame, modif, kernelSize, sigma, sigma);

    cv::imshow(modified_w_title, modif);

  }

  cv::destroyAllWindows();

  return 0;
}

// example-2-5.cpp ends here