//
//  video_writer.cpp 
//  opencv-samples
//
//  Created by Alexandre Biguet on 29/07/2018 at 15:09.
//

// From the opencv doc
// https://docs.opencv.org/2.4/doc/tutorials/highgui/video-write/video-write.html#videowritehighgui
// with small modifs

#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

using namespace std;
using namespace cv;

static void help()
{
  cout
      << "-----------------------------------------------------------------" << endl
      << "This program shows how to write video files."                      << endl
      << "You can extract the R or G or B color channel of the input video." << endl
      << "Usage:"                                                            << endl
      << "./video-write inputvideoName [ R | G | B] [Y | N]"                 << endl
      << "-----------------------------------------------------------------" << endl
      << endl;
}

int main(int argc, char *argv[]) {

  if (argc != 4) {
    cout << "Not enough parameters" << endl;
    help();
    return -1;
  }

  // the source file name
  const string source = argv[1];

  // If false it will use the inputs codec type
  const bool askOutputType = (argv[3][0] =='Y');

  // Open input
  VideoCapture inputVideo(source);

  if (!inputVideo.isOpened()) {
    cout  << "Could not open the input video: " << source << endl;
    return -1;
  }

  // Find extension point
  string::size_type pAt = source.find_last_of('.');

  // Form the new name with container
  const string NAME = source.substr(0, pAt) + argv[2][0] + ".avi";

  // Get Codec Type- Int form
  int ex = static_cast<int>(inputVideo.get(CV_CAP_PROP_FOURCC));

  // Transform from int to char via Bitwise operators
  char EXT[] = {(char)(ex & 0XFF) ,
                (char)((ex & 0XFF00) >> 8),
                (char)((ex & 0XFF0000) >> 16),
                (char)((ex & 0XFF000000) >> 24), 0};

  // Acquire input size
  Size S = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH),
                (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));

  // Open the output
  VideoWriter outputVideo;

  if (askOutputType) {
    outputVideo.open(NAME, ex = -1, inputVideo.get(CV_CAP_PROP_FPS), S, true);
  } else {
    outputVideo.open(NAME, ex, inputVideo.get(CV_CAP_PROP_FPS), S, true);
  }

  if (!outputVideo.isOpened()) {
    cout  << "Could not open the output video for write: " << source << endl;
    return -1;
  }

  cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
       << " of nr#: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
  cout << "Input codec type: " << EXT << endl;

  // Select the channel to save
  int channel = 2;

  switch(argv[2][0]) {
    case 'R' : {
      channel = 2;
      break;
    }
    case 'G' : {
      channel = 1;
      break;
    }
    case 'B' : {
      channel = 0;
      break;
    }
    default:
      break;
  }

  Mat src, res;

  vector<Mat> spl;

  // Show the image captured in the window and repeat
  for(;;)
  {
    // read
    inputVideo >> src;

    // check if at end
    if (src.empty()){
      break;
    }

    // process - extract only the correct channel
    split(src, spl);

    for (int i =0; i < 3; ++i) {
      if (i != channel) {
        spl[i] = Mat::zeros(S, spl[0].type());
      }
    }

    merge(spl, res);

    //outputVideo.write(res); //save or
    outputVideo << res;
  }

  cout << "Finished writing" << endl;
  return 0;
}


// video_writer.cpp ends here