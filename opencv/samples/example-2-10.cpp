//
//  example-2-10.cpp 
//  opencv-samples
//
//  Created by Alexandre Biguet on 28/07/2018 at 15:23.
//

/**
 * Input from camera.
 * Saving the output to file if wanted
 */

#define PRINT_ARGS_TO_STDOUT

#include <iostream>
#include <memory>

#include <boost/optional.hpp>

#include <opencv2/opencv.hpp>

#include <docopt.h>

// ----------------------------------------------------------------------------

static const char USAGE[] =
    R"(example-2-10.

Usage:
  example-2-10 [options] canny [--downsample | --upsample] [--blur-first]

Options:
  -h --help             Shows this help
  -V --version          Shows the version
  --framerate <rate>    waitKey argument [unit : ms]
  --save <filename>     Saves the output to file

)";

// ----------------------------------------------------------------------------

using MapArgs = std::map<std::string, docopt::value>;

// ----------------------------------------------------------------------------

void apply(const cv::Mat& original,
           cv::Mat& modified,
           const std::unique_ptr<MapArgs>& args);

// ----------------------------------------------------------------------------

int main(int argc, char ** argv) {

  std::unique_ptr<MapArgs> args (nullptr);
  uint framerate_ms(30);


  if (argc > 1) {

    args = std::make_unique<MapArgs> (
        docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "test version"));

#ifdef PRINT_ARGS_TO_STDOUT
    for (auto const& arg : *args) {
      std::cout << "| " << arg.first << " | " << arg.second << std::endl;
    }
#endif

    if (args->at("--framerate").isLong()) {
      auto rate = args->at("<rate>").asLong();
      if (rate <= 0) {
        throw std::invalid_argument("framerate should be > 0");
      }
      framerate_ms = static_cast<uint>(rate);
    }

  }

  cv::VideoCapture capture;
  capture.open(0);

  if (! capture.isOpened()) {
    std::cout << "could not open camera device \n";
    return -1;
  }

  cv::namedWindow("input");
  cv::namedWindow("modified");

  cv::Mat input, modified;

  std::string filename;
  cv::VideoWriter writer;

  if (args->at("--save").isString()) {

    // TODO
    std::cout << "?????? CV_FOURCC : check value ??????" << std::endl;

    filename = args->at("--save").asString();

    double input_fps    = capture.get(CV_CAP_PROP_FPS);
    double input_width  = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    double input_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);

    // TODO : if downsample / update sample is used, then the ouput width
    //        and height are different from input

    std::cout << "video saved to : " << filename << "\n"
              << "   - fps    : " << input_fps << "\n"
              << "   - width  : " << input_width << "\n"
              << "   - height : " << input_height << "\n";

    writer.open(filename, CV_FOURCC('I', 'Y', 'U', 'V'),
                input_fps, cv::Size((int) input_width,(int) input_height));
  }


  for(;;) {

    capture >> input;

    if (input.empty()) {
      break;
    }

    apply(input, modified, args);

    cv::imshow("input", input);

    cv::imshow("modified", modified);

    writer << modified;

    auto key = cv::waitKey(framerate_ms);

    if (key == 'k') {
      break;
    }

  }

  cv::destroyAllWindows();

  return 0;
}

// ----------------------------------------------------------------------------

void apply(const cv::Mat& original,
           cv::Mat& modified,
           const std::unique_ptr<MapArgs>& args) {

  if (! args) {
    modified = original;
    return;
  }

  if (args->at("canny").asBool()) {

    cv::Mat canny, scaled, blurred;

    if (args->at("--blur-first")) {
      cv::GaussianBlur(original, blurred, cv::Size(9,9), 30.0);
    } else {
      blurred = original;
    }

    if (args->at("--downsample")) {
      cv::pyrDown(blurred, scaled);
    } else if (args->at("--upsample")) {
      cv::pyrUp(blurred, scaled);
    } else {
      scaled = blurred;
    }

    double th1(10.0), th2(100.0);

    cv::Canny(scaled, modified, th1, th2);
  }

}

// example-2-10.cpp ends here