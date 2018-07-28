//
//  example-2-9.cpp 
//  opencv-samples
//
//  Created by Alexandre Biguet on 28/07/2018 at 12:29.
//

/**
 * Following example-2-8.
 * Reading and writing pixel values
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

  const uint ndown = 2;
  cv::Mat tmp, down;
  cv::pyrDown(igray, down);
  uint count(ndown);
  while (count != 1) {
    down.copyTo(tmp);
    cv::pyrDown(tmp, down);
    --count;
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

  // 5- reading / writing pixel values

  cv::Mat canny_cpy;
  canny.copyTo(canny_cpy);

  int col(16), row(32);
  cv::Vec3b intensity = input.at<cv::Vec3b>(row, col);

  auto blue  = static_cast<uint>(intensity[0]);
  auto green = static_cast<uint>(intensity[1]);
  auto red   = static_cast<uint>(intensity[2]);

  std::cout << "Input image : \n"
            << " (row : " << row << " ; col : " << col << " ) \n"
            << " [blue, green, red] = [ "
            << blue << "; " << green << "; " << red << " ] \n";

  std::cout << "Grayscale image : \n"
            << " [gray] = [ " << static_cast<uint>(igray.at<uchar>(row, col))
            << " ]\n";

  col /= (2*ndown);
  row /= (2*ndown);

  std::cout << "Canny image : \n"
            << " (row : " << row << " ; col : " << col << " ) \n"
            << " [gray] = [ " << static_cast<uint>(canny.at<uchar>(row, col))
            << " ]\n";

  canny_cpy.at<uchar>(row, col) = 128;

  std::cout << "Canny copied image : \n"
            << " (row : " << row << " ; col : " << col << " ) \n"
            << " [gray] = [ "
            << static_cast<uint>(canny_cpy.at<uchar>(row, col)) << " ]\n";

  // Obvioulsy this works. Can we set entire row / col
  // With the following, you should see a white line (in canny_cpy) starting
  // in upper left corner as y = -x

  const int wide = 100;
  uchar px_value = 255;
  for (int i = 0; i < col+wide ;++i) {
    canny_cpy.at<uchar>(i, i) = px_value;
    canny_cpy.at<uchar>(i+1, i) = px_value;
    canny_cpy.at<uchar>(i-1, i) = px_value;
  }

  // -End- outputs images
  // See example-2-8 for an ouptut of all the images used / constructed in the
  // program

  cv::namedWindow("downsampled");
  cv::namedWindow("canny");
  cv::namedWindow("canny-cpy");
  cv::imshow("dowsampled", down);
  cv::imshow("canny", canny);
  cv::imshow("canny-cpy", canny_cpy);

  cv::waitKey(0);

  return 0;
}


// example-2-9.cpp ends here