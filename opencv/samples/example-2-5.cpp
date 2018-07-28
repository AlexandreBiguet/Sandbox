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

// Note : this is just test. If you read that, you will find
//  - no coding style
//  - no optimization (not at all)
//  - code duplication

#define PRINT_ARGS_TO_STDOUT

#include <iostream>
#include <memory>

#include <boost/optional.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <docopt.h>

static const char USAGE[] =
    R"(example-2-5.

  Usage:
    example-2-5 [options] gaussian-blur (<video-path>)
                          [(--ksize <ksize>)] [(--sigma <sigma>)]
    example-2-5 [options] median-blur (<video-path>) [--ksize <ksize>]
    example-2-5 [options] bilateral (<video-path>)
                          [(--sigma-color <color>)] [(--sigma-space <space>)]
                          [(--diameter <diameter>)]
    example-2-5 [options] box-filter (<video-path>) [--ksize <ksize>]

  Options:
    -h --help       Shows this help
    --version       Shows the version
    --nblur <nblur> number of time to blur the original image
 )";

using MapArgs = std::map<std::string, docopt::value>;

enum class BlurType {
  Gaussian, Median, BilateralFilter, BoxFilter, Undefined};

static const std::map<BlurType, std::string> BlurTypeString { /* NOLINT */
    {BlurType::Gaussian, "Gaussian Blur"},
    {BlurType::Median, "Median Blur"},
    {BlurType::BilateralFilter, "Bilateral Filter"},
    {BlurType::BoxFilter, "Box Filter"},
    {BlurType::Undefined, "Undefined Blur"}
};

// forward declaration of Options structure
struct Options;

struct Bluring {
  virtual ~Bluring() = default;
  virtual void apply(const cv::Mat& original,
                     cv::Mat& modified, const Options& opts) = 0;
};

struct Options {

  /// \brief Construction of program options from the command line arguments
  Options(int argc, char** argv);

  /// \brief prints the options to stdout
  void show() const;

  /// \brief Access a bluring algo implementation ptr
  /// \return a ptr to a bluring algo
  std::shared_ptr<Bluring> getImplementation() const;

  /// Blur type to be used
  BlurType _type;

  /// path to the video file
  std::string _video;

  /// Blurring is applied _nblur times
  uint _nblur;

  /// From OpenCV doc.
  /// ksize Gaussian kernel size. ksize.width and ksize.height can differ but
  /// they both must be positive and odd. Or, they can be zero's and then they
  /// are computed from sigma.
  /// Kernel size used for gaussian and median blur
  boost::optional<uint> _kernelSize;

  /// From OpenCV doc.
  /// sigmaX Gaussian kernel standard deviation in X direction.
  /// sigmaY Gaussian kernel standard deviation in Y direction;
  /// if sigmaY is zero, it is set to be equal to sigmaX, if both sigmas are
  /// zeros, they are computed from ksize.width and ksize.height, respectively
  /// (see #getGaussianKernel for details); to fully control the result
  /// regardless of possible future modifications of all this semantics, it
  /// is recommended to specify all of ksize, sigmaX, and sigmaY.
  /// gaussian blur sigma (x and y) values.
  boost::optional<double> _sigma;

  /// From OpenCV doc.
  /// Diameter of each pixel neighborhood that is used during filtering.
  /// If it is non-positive, it is computed from sigmaSpace.
  /// diameter used in the bilateral filter
  boost::optional<int> _diameter;

  /// From OpenCV doc.
  /// Filter sigma in the color space. A larger value of the parameter means
  /// that farther colors within the pixel neighborhood (see sigmaSpace) will
  /// be mixed together, resulting in larger areas of semi-equal color.
  /// Used in the bilateral filter
  boost::optional<double> _sigmaColor;

  /// From OpenCV doc.
  /// Filter sigma in the coordinate space. A larger value of the parameter
  /// means that farther pixels will influence each other as long as their
  /// colors are close enough (see sigmaColor). When d\>0, it specifies the
  /// neighborhood size regardless of sigmaSpace. Otherwise, the diameter is
  /// proportional to sigmaSpace.
  /// Used in the bilateral filter
  boost::optional<double> _sigmaSpace;

};


struct GaussianBluring : public Bluring {
  void apply(const cv::Mat& original,
             cv::Mat& modified, const Options& opts) override;
};

struct MedianBluring : public Bluring {
  void apply(const cv::Mat& original,
             cv::Mat& modified, const Options& opts) override;
};

struct BilateralBluring : public Bluring {
  void apply(const cv::Mat& original,
             cv::Mat& modified, const Options& opts) override;
};

struct BoxFilter : public Bluring {
  void apply(const cv::Mat& original,
             cv::Mat& modified, const Options& opts) override;
};

int main(int argc, char** argv) {

  Options opts(argc, argv);
  opts.show();

  std::string original_w_title("original");
  std::string modified_w_title("modified");
  cv::VideoCapture capture;
  capture.open(opts._video);

  std::shared_ptr<Bluring> bluringPtr = opts.getImplementation();

  cv::namedWindow(original_w_title, cv::WINDOW_NORMAL);
  cv::namedWindow(modified_w_title, cv::WINDOW_NORMAL);

  cv::moveWindow(original_w_title, -10, 10);
  cv::moveWindow(modified_w_title, 400, 400);

  cv::Mat frame, modif, tmp;

  // tmp is used for bluring algos which does not support inplace modifs

  // TODO 1 :
  // check if '=' operator is a deep copy, or if this is just some kind ptr
  // instance increment.

  // TODO 2 :
  // check what they mean in the doc by inplace application

  // TODO 3 :
  // check if the cv::[Input / Output] Array type is a kind of GstBuffer.
  // If not, try implementation :-)

  for (;;) {
    capture >> frame;

    auto c = static_cast<char> (cv::waitKey(30));

    if (c == 'k' || frame.empty()) {
      break;
    }

    cv::imshow(original_w_title, frame);

    bluringPtr->apply(frame, modif, opts);

    if (opts._nblur > 1) {
      int n = opts._nblur;
      while (n != 1) {
        // tmp = modif;
        modif.copyTo(tmp);
        bluringPtr->apply(tmp, modif, opts);
        --n;
      }
    }

    cv::imshow(modified_w_title, modif);

  }

  cv::destroyAllWindows();

  return 0;
}

static double toDouble(const std::string& str) {
  try {
    return std::stod(str);
  } catch(...) {
    std::cout << "could not convert string to double properly. \n";
    return 0.0;
  }
}

Options::Options(int argc, char **argv)
    : _type(BlurType::Undefined) ,
      _sigma(30.0),
      _kernelSize(5),
      _nblur(1),
      _sigmaColor(10.0),
      _diameter(5), // TODO sigmaSpace and diameter should not be set together (?)
      _sigmaSpace(15.0) {

  MapArgs args =
      docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "test version");

#ifdef PRINT_ARGS_TO_STDOUT
  for (auto const& arg : args) {
    std::cout << "| " << arg.first << " | " << arg.second << std::endl;
  }
#endif

  if (args["gaussian-blur"].asBool()) {
    _type = BlurType::Gaussian;
  } else if (args["median-blur"].asBool()) {
    _type = BlurType::Median;
  } else if (args["bilateral"].asBool()) {
    _type = BlurType::BilateralFilter;
  } else if (args["box-filter"].asBool()) {
    _type = BlurType::BoxFilter;
  } else {
    throw std::runtime_error("blur type cannot be undefined");
  }

  if (args["--nblur"]) {
    auto nblur = args["--nblur"].asLong();
    if (nblur <= 0) {
      throw std::invalid_argument(" --nblur argument must be > 0 \n");
    }

    _nblur = static_cast<uint> (nblur);
  }

  if (args["--ksize"].asBool()) {
    auto kernelSize = args["<ksize>"].asLong();
    if (kernelSize % 2 == 0) {
      throw std::invalid_argument("gaussian kernel size must be odd");
    }

    if (kernelSize < 1) {
      throw std::invalid_argument("gaussian kernel size must >= 1");
    }

    _kernelSize = static_cast<uint> (kernelSize);
  }

  if (args["--sigma"].asBool()) {
    _sigma = toDouble(args["<sigma>"].asString());
  }

  _video = args["<video-path>"].asString();

  if (args["--sigma-color"].asBool()) {
    _sigmaColor = toDouble(args["<color>"].asString());
  }

  if (args["--sigma-space"].asBool()) {
    _sigmaSpace = toDouble(args["<space>"].asString());
  }

  if (args["--diameter"].asBool()) {
    _diameter = toDouble(args["<diameter>"].asString());
  }

}

template <typename T>
std::string toString(const boost::optional<T>& b) {
  if (b) {
    return std::to_string(*b);
  }
  return {"Undefined / Default"};
}

void Options::show() const {
  std::cout << " - blur type   : " << BlurTypeString.at(_type) << "\n";
  std::cout << " - kernel size : " << toString(_kernelSize) << "\n";
  std::cout << " - sigma       : " << toString(_sigma) << "\n";
  std::cout << " - n blur      : " << std::to_string(_nblur) << "\n";
  std::cout << " - video path  : " << _video << "\n";
}

void GaussianBluring::apply(
    const cv::Mat &original, cv::Mat &modified, const Options& opts) {

  auto ks = *opts._kernelSize;
  auto sigma = *opts._sigma;
  cv::Size kernelSize(ks, ks);

  cv::GaussianBlur(original, modified, kernelSize, sigma, sigma);

}

void MedianBluring::apply(const cv::Mat &original,
                          cv::Mat &modified,
                          const Options &opts) {
  cv::medianBlur(original, modified, *opts._kernelSize);
}

void BilateralBluring::apply(const cv::Mat &original,
                             cv::Mat &modified,
                             const Options &opts) {

  cv::bilateralFilter(original, modified,
      *opts._diameter, *opts._sigmaColor, *opts._sigmaSpace);

}

std::shared_ptr<Bluring> Options::getImplementation() const {
  std::shared_ptr<Bluring> ptr(nullptr);

  if (_type == BlurType::Median) {
    ptr = std::make_shared<MedianBluring>();
  } else if (_type == BlurType::Gaussian) {
    ptr = std::make_shared<GaussianBluring>();
  } else if (_type == BlurType::BilateralFilter) {
    ptr = std::make_shared<BilateralBluring>();
  } else if (_type == BlurType::BoxFilter)  {
    ptr = std::make_shared<BoxFilter>();
  } else {
    throw std::runtime_error("not possible");
  }

  return ptr;
}

void BoxFilter::apply(const cv::Mat &original,
                      cv::Mat &modified,
                      const Options &opts) {

  auto ks = *opts._kernelSize;
  cv::boxFilter(original, modified, -1, cv::Size(ks,ks));

}

// example-2-5.cpp ends here
