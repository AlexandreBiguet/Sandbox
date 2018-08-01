//
//  segment_object.cpp
//  opencv-samples
//
//  Created by Alexandre Biguet on 01/08/2018 at 11:43.
//

// From opencv tuto
// https://docs.opencv.org/master/dd/d9d/segment_objects_8cpp-example.html#a24

#include <iostream>
#include <string>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/videoio.hpp>

#include <utils/utils.hpp>

// ----------------------------------------------------------------------------

static const char USAGE[] =
    R"(segobj.

Usage:
  segobj info
  segobj [options] (cam | video (<path>)) [--variance-threshold (<var>)]

Options:
  -h --help             Shows this help
  --framerate <rate>    waitKey argument [unit : ms]
)";

// ----------------------------------------------------------------------------

void info();

void refineSegments(const cv::Mat& img, cv::Mat& mask, cv::Mat& dst,
                    int niters = 3);

// ----------------------------------------------------------------------------

static double g_variance_threshold = 10.0;

int main(int argc, char** argv) {

  cv_samples::utils::MapArgs args =
      docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "v0");

  cv_samples::utils::print_docargs(args);

  if (args["info"].asBool()) {
    info();
    std::cout << "\n    --help for program options \n";
    return 0;
  }

  cv::VideoCapture capture;

  if (args["cam"].asBool()) {
    std::cout << "--> using webcam \n";
    capture.open(0);
  } else if (args["video"].asBool()) {
    std::string path(args["<path>"].asString());
    std::cout << "video : " << path << std::endl;
    capture.open(path);
  }

  bool update_bg_model = true;

  if (!capture.isOpened()) {
    printf("\nCan not open camera or video file\n");
    return -1;
  }

  cv::Mat tmp_frame, bgmask, out_frame;

  cv::namedWindow("video", 1);
  cv::namedWindow("segmented", 1);

  cv::Ptr<cv::BackgroundSubtractorMOG2>
      bgsubtractor = cv::createBackgroundSubtractorMOG2();

  bgsubtractor->setVarThreshold(g_variance_threshold);

  if (args["--variance-threshold"].asBool()) {
    bgsubtractor->setVarThreshold(std::stod(args["<var>"].asString()));
  }

  for (;;) {
    capture >> tmp_frame;

    if (tmp_frame.empty()) {
      break;
    }

    bgsubtractor->apply(tmp_frame, bgmask, update_bg_model ? -1 : 0);

    refineSegments(tmp_frame, bgmask, out_frame);

    cv::imshow("video", tmp_frame);
    cv::imshow("segmented", out_frame);

    char keycode = (char) cv::waitKey(30);

    if (keycode == 27) {
      break;
    }

    if (keycode == ' ') {
      update_bg_model = !update_bg_model;
      printf("Learn background is in state = %d\n", update_bg_model);
    }
  }
  return 0;
}

// ----------------------------------------------------------------------------

void info() {
  std::cout << "This program demonstrated a simple method of connected "
               "components clean up of background subtraction\n"
               "When the program starts, it begins learning the background.\n"
               "You can toggle background learning on and off by hitting "
               "the space bar.\n";
}

// ----------------------------------------------------------------------------

void refineSegments(const cv::Mat& img, cv::Mat& mask, cv::Mat& dst,
                    int niters) {
  std::vector<std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::Mat temp;
  cv::dilate(mask, temp, cv::Mat(), cv::Point(-1, -1), niters);
  cv::erode(temp, temp, cv::Mat(), cv::Point(-1, -1), niters * 2);
  cv::dilate(temp, temp, cv::Mat(), cv::Point(-1, -1), niters);
  cv::findContours(temp, contours, hierarchy, cv::RETR_CCOMP,
                   cv::CHAIN_APPROX_SIMPLE);

  if (contours.empty()) {
    return;
  }

  dst = cv::Mat::zeros(img.size(), CV_8UC3);

  // iterate through all the top-level contours,
  // draw each connected component with its own random color

  int idx (0);
  int largestComp(0);
  double maxArea(0.0);

  for (; idx >= 0; idx = hierarchy[idx][0]) {
    const std::vector<cv::Point>& c = contours[idx];
    double area = fabs(cv::contourArea(cv::Mat(c)));
    if (area > maxArea) {
      maxArea = area;
      largestComp = idx;
    }
  }

  cv::Scalar color(0, 0, 255);
  cv::drawContours(dst, contours, largestComp, color,
                   cv::FILLED, cv::LINE_8, hierarchy);
}

// ----------------------------------------------------------------------------


// segment_object.cpp ends here
