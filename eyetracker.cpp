/**
 * @file eyetracker.cpp
 * @brief EyeTracker
 *
 * Image Processing and Pattern Recognition
 * (Bildverarbeitung und Mustererkennung)
 * Project
 */

#include "eyetracker.h"
#include "eyecapture.cpp"
#include "headcapture.cpp"
#include "tracking/trackingEyeHough.cpp"

#define EYE_CAM 0
#define HEAD_CAM 0
#define VIDEO_OUTPUT 0
#define CONVERT_TO_GRAY 1

/**
 * @brief The main entry point 
 */
int main(int /*argc*/, char ** /*argv*/)
{
  TrackingEyeHough eye(EYE_CAM);

  TrackedPupil pupil;

  cv::Mat frame;
  cv::Mat head_frame;

  cv::VideoWriter writer;
  if(VIDEO_OUTPUT)
  {
    writer.open("output.avi", CV_FOURCC('X','V','I','D'), 10, cv::Size(640, 480));
    if (!writer.isOpened())
    {
      std::cout << "[Error] Cannot encode video with fallback codec!" << std::endl;
      return -1;
    }
  }

  //HeadCapture head(HEAD_CAM, CONVERT_TO_GRAY);

  for(;;)
  {
    pupil = eye.getPupil();
    frame = pupil.frame.clone();

    //head_frame = head.getFrame();

    if (frame.empty())
    {
      std::cout << "[Warning] Skipping empty frame." << std::endl;
      continue;
    }

    //for(int i = 0; i < pupil.position.size(); i++)
    for(int i = 0; i < 1; i++)
    {
      cv::circle(frame, cv::Point(pupil.position[i].x, pupil.position[i].y), pupil.radius[i], cv::Scalar(255), 2);
    }

    // show eye frame
    cv::imshow("eye", frame);
    if(cv::waitKey(10) >= 0) break;

    // show head frame
    //cv::imshow("head", head_frame);
    //if(cv::waitKey(10) >= 0) break;


    if(VIDEO_OUTPUT)
    {
      cv::Mat color;
      cv::cvtColor(frame.clone(), color, CV_GRAY2BGR);
      writer << color;
    }
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
