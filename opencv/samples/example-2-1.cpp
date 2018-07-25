#include <iostream>

#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "need one arg (a path to an image) \n";
    return -1;
  }

  cv::Mat img = cv::imread(argv[1], -1);

  if (img.empty()) {
    std::cout << "image not read \n";
    return -1;
  }

  cv::namedWindow("window title", cv::WINDOW_AUTOSIZE);

  cv::imshow("window title", img);

  cv::waitKey(0);

  cv::destroyWindow("window title");

  return 0;
}
