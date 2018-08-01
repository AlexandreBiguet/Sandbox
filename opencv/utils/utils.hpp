//
//  utils.hpp 
//  opencv-samples
//
//  Created by Alexandre Biguet on 31/07/2018 at 16:21.
//
#pragma once

#include <docopt.h>
#include <opencv2/core.hpp>
#include "../../../../../../../../usr/local/Cellar/opencv/3.4.2/include/opencv2/videoio.hpp"

namespace cv_samples { namespace utils {

/// \brief typedef for docopt command line parsing
using MapArgs = std::map<std::string, docopt::value>;

/// \brief prints the command line arguments to stdout
/// \note debug only
/// \param args a map of docopt args
void print_docargs(const MapArgs& args);

/// \brief Found in some opencv stuff. From a CV_FOURCC integer value,
/// computes the corresponding string
/// \param fourcc a CV_FOURCC int. value
/// \return the string corresponding to the CV_FOURCC
std::string get_fourcc(int fourcc);

/// \brief The PSNR returns a float number, that if the two inputs are similar
///        between 30 and 50 (higher is better).
/// \note see https://en.wikipedia.org/wiki/Peak_signal-to-noise_ratio
/// \note GPU version can be found here:
/// https://docs.opencv.org/2.4/doc/tutorials/gpu/gpu-basics-similarity/gpu-basics-similarity.html
/// \from https://docs.opencv.org/master/d5/dc4/tutorial_video_input_psnr_ssim.html
/// \param I1 input matrix
/// \param I2 input matrix
/// \return a double prec. nb [Unit: decibel dB]
double get_PSNR(const cv::Mat& I1, const cv::Mat& I2);

/// \brief computes the structural similarity
/// \note see https://en.wikipedia.org/wiki/Structural_similarity
/// \note from https://docs.opencv.org/master/d5/dc4/tutorial_video_input_psnr_ssim.html
/// \note GPU version can be found here:
/// https://docs.opencv.org/2.4/doc/tutorials/gpu/gpu-basics-similarity/gpu-basics-similarity.html
/// \param i1
/// \param i2
/// \return a float number between zero and one (higher is better), one for
///         each channel
cv::Scalar get_MSSIM(const cv::Mat& i1, const cv::Mat& i2,
    double C1 = 6.5025, double C2 = 58.5225);

/// \brief Helper. Gets the size of a video capture instance
/// \param cap input capture
/// \return size of the input capture
cv::Size get_capture_size(const cv::VideoCapture& cap);

}
} // namespace opencv-samples 

// utils.hpp ends here