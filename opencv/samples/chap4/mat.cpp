//
//  e1.cpp 
//  opencv-samples
//
//  Created by Alexandre Biguet on 30/07/2018 at 12:24.
//

#include <iostream>

#include <opencv2/opencv.hpp>

int main() {

  cv::Mat mat;

  /**
   * List of mat type :
   * ------------------
   * CV_8U  - 8-bit unsigned integers ( 0..255 )
   * CV_8S  - 8-bit signed integers ( -128..127 )
   * CV_16U - 16-bit unsigned integers ( 0..65535 )
   * CV_16S - 16-bit signed integers ( -32768..32767 )
   * CV_32S - 32-bit signed integers ( -2147483648..2147483647 )
   * CV_32F - 32-bit floating-point numbers ( -FLT_MAX..FLT_MAX, INF, NAN )
   * CV_64F - 64-bit floating-point numbers ( -DBL_MAX..DBL_MAX, INF, NAN )
   *
   * CV_<bit-depth>{U|S|F}C<number_of_channels>
   *
   */

  mat.create(10, 5, CV_8SC3);
  mat.setTo(cv::Scalar(1, 2, 3));

  std::cout << mat << "\n";

  std::cout << "size  : " << mat.size << "\n";
  std::cout << "depth : " << mat.depth() << "\n";
  std::cout << "cols  : " << mat.cols << "\n";
  std::cout << "rows  : " << mat.rows << "\n";
  std::cout << "flags : " << mat.flags << "\n";

  {
    int nrow(100), ncol(100);
    auto type = CV_8SC3;
    cv::Mat b(nrow, ncol, type, cv::Scalar(255, 0, 0)); // BGR
    cv::Mat r(nrow, ncol, type, cv::Scalar(0, 0, 255));
    cv::Mat w(nrow, ncol, type, cv::Scalar(255, 255, 255));

    // To construct the flag we want to 'concat' the b, w and r matrices.
    // The idea is to construct a sufficiently large destination matrix and
    // to copy the value of the b, w, r matrices to the proper ROI's
    // (in the destination matrix)

    cv::Mat dst(nrow, 3*ncol, type, cv::Scalar(0, 0, 0));

    b.copyTo(dst(cv::Rect(0, 0, b.cols, b.rows)));
    w.copyTo(dst(cv::Rect(b.cols, 0, w.cols, w.rows)));
    r.copyTo(dst(cv::Rect(2*ncol, 0, r.cols, r.rows)));

    cv::namedWindow("flag");
    cv::imshow("flag", dst);
    auto key = cv::waitKey(0);
    if (key == 'k') {
      cv::destroyAllWindows();
    }

  }

  return 0;
}

// mat.cpp ends here