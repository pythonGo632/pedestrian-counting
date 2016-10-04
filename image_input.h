/* image_input.h
 * class for retrieving camera input regardless of whether it's a stream or file
 */

#ifndef IMAGE_INPUT_H
#define IMAGE_INPUT_H

#include <raspicam/raspicam_cv.h>
#include <opencv/cv.hpp>

using namespace cv;
using namespace std;

class ImageInput {
public:
  // Constructor for live feed
  ImageInput();
  // Constructor for video from file
  ImageInput(String vid_name);
  // Generic destructor
  ~ImageInput();
  // opens the capture
  bool open();
  // Get next frame
  bool read(Mat& frame);
  // Release input
  void release();
private:
  bool         isLive;            // whether to use a live stream or video file
  string       vid_name;          // filepath of video, if capturing from file
  VideoCapture vid_capture;       // object to read video from file
  raspicam::RaspiCam_Cv rasp_cam; // object to get images from raspberry pi's camera
};

 #endif
