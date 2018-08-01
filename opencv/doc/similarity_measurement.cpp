//
//  similarity_measurement.cpp
//  opencv-samples
//
//  Created by Alexandre Biguet on 31/07/2018 at 15:33.
//

// From the doc
// https://docs.opencv.org/master/d5/dc4/tutorial_video_input_psnr_ssim.html

/// \brief small program that reads in two video files and performs a
/// similarity check between them.
/// Use case : check how well a new video compressing algorithms works.

/// First : computation of the PSNR (signal over noise)
/// (see https://en.wikipedia.org/wiki/Peak_signal-to-noise_ratio)
/// If the computed value is below a threshold, computes a SSIM
/// (structural similarity between them)

#define PRINT_ARGS_TO_STDOUT

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/format.hpp>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>

#include <utils/utils.hpp>

const char USAGE[] = R"(
simmeas.

Usage:
  simmeas psnr (<img1>) (<img2>)
  simmeas ssim (<img1>) (<img2>)
  simmeas [options] (<video1>) (<video2>)

Options:
  -h --help                Shows this help
  --psnr-trigger <trigger> The PSNR trigger value
  --delay_ms <delay>       The delay between two frames (unit : ms)
)";

// ----------------------------------------------------------------------------

struct Options {

  /// path to the video 1 (image 1)
  std::string _path1;

  /// path to the video 2 (image 2)
  std::string _path2;

  /// value to the psnr trigger (only used when comparing two videos)
  double _psnr_trigger;

  /// delay between each frames (only used when comparing two videos)
  int _delay_ms;

  /// A copy of the parsed command line args
  cv_samples::utils::MapArgs _args;

  /// \brief Construction from command line arguments
  /// \param argc
  /// \param argv
  Options(int argc, char** argv) : _psnr_trigger(0.0), _delay_ms(50) {

    // Parsing command line arguments

    _args = docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "V0");

    std::vector<std::string> paths1{"<img1>", "<video1>"};
    std::vector<std::string> paths2{"<img2>", "<video2>"};

    for(const auto& p : paths1) {
      if (_args[p].isString()) {
        _path1 = _args[p].asString();
        break;
      }
    }

    for(const auto& p : paths2) {
      if (_args[p].isString()) {
        _path2 = _args[p].asString();
        break;
      }
    }

    if (_args["--psnr-trigger"].isString()) {
      _psnr_trigger = std::stod(_args["--psnr-trigger"].asString());
    }

    if (_args["--delay_ms"].isString()) {
      _delay_ms = static_cast<int>(_args["--delay_ms"].asLong());
    }

  }

  /// \brief debug only
  void show() const {

#ifdef PRINT_ARGS_TO_STDOUT
    cv_samples::utils::print_docargs(_args);
#endif

    std::cout << std::endl;
    std::cout << "path 1       : " << _path1 << "\n";
    std::cout << "path 2       : " << _path2 << "\n";
    std::cout << "psnr trigger : " << _psnr_trigger << "\n";
    std::cout << "delay        : " << _delay_ms << "\n";

  }

};

// ----------------------------------------------------------------------------

void print_mssim(const cv::Scalar& mssim);

// ----------------------------------------------------------------------------

int main(int argc, char** argv) {

  Options opts(argc, argv);

  opts.show();

  // Image comparison

  if (opts._args["psnr"].asBool() || opts._args["ssim"].asBool()) {

    cv::Mat img1 = cv::imread(opts._path1);
    cv::Mat img2 = cv::imread(opts._path2);

    if (img1.empty() || img2.empty()) {
      std::cout << "image not read properly" << std::endl;
    }

    if (opts._args["psnr"].asBool()) {
      double psnr = cv_samples::utils::get_PSNR(img1, img2);
      std::cout << boost::format("%15.7f") % psnr << std::endl;
    }

    if (opts._args["ssim"].asBool()) {
      cv::Scalar value = cv_samples::utils::get_MSSIM(img1, img2);
      std::cout << value << std::endl;
    }

    return 0;
  }

  // video comparison

  // Frame counter
  int frameNum = -1;

  cv::VideoCapture cap_ref(opts._path1), cap_test(opts._path2);

  if (!cap_ref.isOpened()) {
    std::cout << "Could not open reference " << opts._path1 << std::endl;
    return -1;
  }

  if (!cap_test.isOpened()) {
    std::cout << "Could not open case test " << opts._path2 << std::endl;
    return -1;
  }

  cv::Size refS = cv_samples::utils::get_capture_size(cap_ref);
  cv::Size uTSi = cv_samples::utils::get_capture_size(cap_test);

  if (refS != uTSi) {
    std::cout << "Error: Inputs should have the same size\n";
    return -1;
  }

  const char* win_test = "Under Test";
  const char* win_ref = "Reference";

  // Windows
  cv::namedWindow(win_ref, cv::WINDOW_AUTOSIZE);
  cv::namedWindow(win_test, cv::WINDOW_AUTOSIZE);
  cv::moveWindow(win_ref, 400, 0);
  cv::moveWindow(win_test, refS.width, 0);

  std::cout << "Reference frame resolution \n";
  std::cout << "[width, height, nframes] = "
            << boost::format("%4d %4d %5d") % refS.width % refS.height
                % (int) cap_ref.get(cv::CAP_PROP_FRAME_COUNT);

  cv::Mat frame_ref, frame_test;

  for (;;)
  {
    cap_ref >> frame_ref;
    cap_test >> frame_test;

    if (frame_ref.empty() || frame_test.empty()) {
      std::cout << "Eof";
      break;
    }

    ++frameNum;

    std::cout << "Frame: " << frameNum << "# ";

    double psnr_value = cv_samples::utils::get_PSNR(frame_ref, frame_test);

    std::cout << "computed psnr : " << psnr_value << "dB";

    if (psnr_value < opts._psnr_trigger) {

      cv::Scalar mssimV = cv_samples::utils::get_MSSIM(frame_ref, frame_test);
      print_mssim(mssimV);
    }

    std::cout << "\n";

    imshow(win_ref, frame_ref);
    imshow(win_test, frame_test);

    char c = (char) cv::waitKey(opts._delay_ms);

    if (c == 27) { /* ESC key */
      break;
    }
  }

  return 0;
}

void print_mssim(const cv::Scalar& mssim) {
  std::cout << "computed mssim (RGB channels):\n";
  std::cout << boost::format("[R : %10.4f] [G: %10.4f] [B: %10.4f]")
      % mssim.val[2] % mssim.val[1] % mssim.val[0];

}

// similarity_measurement.cpp ends here
