//
//  utils.cpp 
//  opencv-samples
//
//  Created by Alexandre Biguet on 31/07/2018 at 16:23.
//

#include "utils.hpp"

#include <iostream>

#include <boost/format.hpp>

#include <opencv2/imgproc.hpp>

namespace cv_samples { namespace utils {

// ----------------------------------------------------------------------------

void print_docargs(const MapArgs& args) {
  std::size_t maxsize(0);
  for (const auto& elem: args) {
    std::size_t size = elem.first.size();
    if (size > maxsize) {
      maxsize = size;
    }
  }

  std::string fmt("%" + std::to_string(maxsize) + "s");

  for (const auto& arg: args) {
    std::cout << "[ " <<boost::format(fmt) % arg.first << " ] [ "
              << arg.second << " ]\n";
  }

}

// ----------------------------------------------------------------------------

std::string get_fourcc(int fourcc)  {
  char EXT[] = {(char)(fourcc & 0XFF) ,
                (char)((fourcc & 0XFF00) >> 8),
                (char)((fourcc & 0XFF0000) >> 16),
                (char)((fourcc & 0XFF000000) >> 24), 0};
  return std::string(EXT);
}

// ----------------------------------------------------------------------------

double get_PSNR(const cv::Mat& I1, const cv::Mat& I2) {
  cv::Mat s1;
  cv::absdiff(I1, I2, s1);       // |I1 - I2|
  s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
  s1 = s1.mul(s1);           // |I1 - I2|^2
  cv::Scalar s = sum(s1);        // sum elements per channel
  double sse = s.val[0] + s.val[1] + s.val[2];  // sum channels

  if (sse <= 1e-10) {
    // for small values return zero
    return 0;
  } else {
    double mse = sse / (double)(I1.channels() * I1.total());
    double psnr = 10.0 * log10((255 * 255) / mse);
    return psnr;
  }
}

// ----------------------------------------------------------------------------

cv::Scalar get_MSSIM(const cv::Mat& i1, const cv::Mat& i2,
                     double C1, double C2) {

  // Inits
  int d = CV_32F;
  cv::Mat I1, I2;
  i1.convertTo(I1, d);  // cannot calculate on one byte large values
  i2.convertTo(I2, d);
  cv::Mat I2_2 = I2.mul(I2);   // I2^2
  cv::Mat I1_2 = I1.mul(I1);   // I1^2
  cv::Mat I1_I2 = I1.mul(I2);  // I1 * I2

  // PRELIMINARY COMPUTING
  cv::Mat mu1, mu2;
  cv::GaussianBlur(I1, mu1, cv::Size(11, 11), 1.5);
  cv::GaussianBlur(I2, mu2, cv::Size(11, 11), 1.5);
  cv::Mat mu1_2 = mu1.mul(mu1);
  cv::Mat mu2_2 = mu2.mul(mu2);
  cv::Mat mu1_mu2 = mu1.mul(mu2);
  cv::Mat sigma1_2, sigma2_2, sigma12;
  cv::GaussianBlur(I1_2, sigma1_2, cv::Size(11, 11), 1.5);
  sigma1_2 -= mu1_2;
  cv::GaussianBlur(I2_2, sigma2_2, cv::Size(11, 11), 1.5);
  sigma2_2 -= mu2_2;
  cv::GaussianBlur(I1_I2, sigma12, cv::Size(11, 11), 1.5);
  sigma12 -= mu1_mu2;
  cv::Mat t1, t2, t3;
  t1 = 2 * mu1_mu2 + C1;
  t2 = 2 * sigma12 + C2;
  t3 = t1.mul(t2);  // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
  t1 = mu1_2 + mu2_2 + C1;
  t2 = sigma1_2 + sigma2_2 + C2;
  t1 = t1.mul(t2);  // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
  cv::Mat ssim_map;
  cv::divide(t3, t1, ssim_map);       // ssim_map =  t3./t1;
  cv::Scalar mssim = cv::mean(ssim_map);  // mssim = average of ssim map
  return mssim;
}

// ----------------------------------------------------------------------------

cv::Size get_capture_size(const cv::VideoCapture& cap) {
  return {static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)),
          static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))};
}

// ----------------------------------------------------------------------------

}
}

// utils.cpp ends here