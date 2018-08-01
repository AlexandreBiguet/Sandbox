//
//  ex10.cpp
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

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/optional.hpp>

#include <opencv2/opencv.hpp>

#include <utils/utils.hpp>

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
  --video-path <path>   Specifies a video to read instead of the O-th camera
  --show                Outputs to screen
  --save-imgs <dir>     Saves the modified images one by one
)";

// ----------------------------------------------------------------------------

void apply(const cv::Mat& original,
           cv::Mat& modified,
           const std::unique_ptr<cv_samples::utils::MapArgs>& args);

// ----------------------------------------------------------------------------

int main(int argc, char ** argv) {

  std::unique_ptr<cv_samples::utils::MapArgs> args (nullptr);
  uint framerate_ms(40);
  bool use_web_cam(true);

  if (argc > 1) {

    args = std::make_unique<cv_samples::utils::MapArgs> (
        docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "v0"));

#ifdef PRINT_ARGS_TO_STDOUT
    cv_samples::utils::print_docargs(*args);
#endif

    if (args->at("--framerate").isLong()) {
      auto rate = args->at("--framerate").asLong();
      if (rate <= 0) {
        throw std::invalid_argument("framerate should be > 0");
      }
      framerate_ms = static_cast<uint>(rate);
    }

    if (args->at("--video-path").isString()) {
      use_web_cam = false;
    }

  }

  cv::VideoCapture capture;
  if (use_web_cam) {
    capture.open(0);
  } else {
    capture.open(args->at("--video-path").asString());
  }

  if (! capture.isOpened()) {
    std::cout << "could not open camera device \n";
    return -1;
  }

  if (args->at("--show").asBool()) {
    cv::namedWindow("input");
    cv::namedWindow("modified");
  }

  std::string filename;
  cv::VideoWriter writer;

  if (args->at("--save").isString()) {

    // TODO
    std::cout << "?????? CV_FOURCC : check value ??????" << std::endl;

    filename = args->at("--save").asString();

    double fps    = capture.get(CV_CAP_PROP_FPS);
    double width  = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    double height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);

    if (args->at("--downsample").asBool()) {
      height /= 2;
      width  /= 2;
    } else if (args->at("--upsample").asBool()) {
      height *= 2;
      width  *= 2;
    }

    std::cout << "video saved to : " << filename << "\n"
              << "   - fps    : " << fps << "\n"
              << "   - width  : " << width << "\n"
              << "   - height : " << height << "\n";

    // auto fourcc = CV_FOURCC('M', 'P', '4', 'V' );
    // auto fourcc = CV_FOURCC('a', 'v', 'c', '1' );
    int fourcc = static_cast<int>(capture.get(CV_CAP_PROP_FOURCC));

    std::cout << "Input fourcc type : "
              << cv_samples::utils::get_fourcc(fourcc) << "\n";

    writer.open(filename, fourcc, fps, cv::Size((int) width,(int) height));

    if (! writer.isOpened()) {
      std::cout << "could not open video writer \n";
    }
  }

  cv::Mat input, modified;
  std::vector<cv::Mat> modified_list;

  for(;;) {

    capture >> input;

    if (input.empty()) {
      break;
    }

    apply(input, modified, args);

    if (args->at("--save-imgs").isString()) {
      modified_list.push_back(modified);
    }

    if (args->at("--show").asBool()) {
      cv::imshow("input", input);
      cv::imshow("modified", modified);
    }

    if (modified.empty()) {
      std::cout << "empty modified frame \n";
    }

    if (writer.isOpened()) {
      writer << modified;
    } else if (args->at("--save").isString()) {
      std::cout << "writer should be opened \n";
    }

    auto key = cv::waitKey(framerate_ms);

    if (key == 'k') {
      break;
    }

    // TODO : why is this mandatory for the images in the list to be different ?
    if (args->at("--save-imgs").isString()) {
      modified.release();
    }

  }

  if (args->at("--save-imgs").isString()) {
    int count(0);
    boost::filesystem::path dir (args->at("--save-imgs").asString());
    if (! boost::filesystem::is_directory(dir)) {
      boost::filesystem::create_directories(dir);
    }

    std::string base("img-");
    for (const auto &img : modified_list) {
      boost::filesystem::path basename =
          dir / (base + (std::to_string(count) + ".jpg"));

      cv::imwrite(basename.string(), img);
      ++count;
    }
  }

  writer.release();
  capture.release();

  if (args->at("--show").asBool()) {
    cv::destroyAllWindows();
  }

  return 0;
}

// ----------------------------------------------------------------------------

void apply(const cv::Mat& original,
           cv::Mat& modified,
           const std::unique_ptr<cv_samples::utils::MapArgs>& args) {

  if (! args) {
    modified = original;
    return;
  }

  if (args->at("canny").asBool()) {

    cv::Mat canny, scaled, blurred;

    if (args->at("--blur-first").asBool()) {
      cv::GaussianBlur(original, blurred, cv::Size(9,9), 30.0);
    } else {
      blurred = original;
    }

    if (args->at("--downsample").asBool()) {
      cv::pyrDown(blurred, scaled);
    } else if (args->at("--upsample").asBool()) {
      cv::pyrUp(blurred, scaled);
    } else {
      scaled = blurred;
    }

    double th1(10.0), th2(100.0);

    cv::Canny(scaled, modified, th1, th2);
  }

}

// example-2-10.cpp ends here