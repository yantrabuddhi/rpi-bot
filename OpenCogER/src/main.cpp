/*
  Project: OpenCogER
  File: main.cpp
  Author: Mandeep Singh Bhatia
  License: AGPL
  Date: May 2017
*/

/*
library functions
capture camera in thread and read image in mute with timestamp
resize image?later
color to gray
equalize histogram
face detection,smile detection, later?object detection
mean shift tracking
save region, time .. later
later: face recognition

make visual detectors .. image ref, rect region,time stamp: in, image ref, count, rect regions,id's, time stamp: out

face detection, smile detection, motion detection, mean shift tracking
improve detection based tracking, nose, mouth, smile, face, eyes
main.cpp or test.cpp
*/
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <vector>
#include <string>

#include "CamCapture.h"
#include "DetectionTrackerBase.h"
#include "color2gray.h"
#include "histEqualize.h"
#include "faceDetect.h"
#include "smileDetect.h"
#include "leftEyeDetect.h"
#include "rightEyeDetect.h"
#include "filterBase.h"

using namespace std;
using namespace cv;

int main()
{
  vector<Rect> faces,smiles;
  unsigned int scount=0;
  cv::Rect face_i;
  cv::namedWindow("Detection Based Tracker",cv::WINDOW_NORMAL);
  Mat img,img2;

  CamCapture cc(320,240,1);
  smileDetect sd;
  color2gray c2g;
  DetectionTrackerBase dt("face","haarcascade_frontalface_alt.xml",&cc);
  dt.run();
  //img=cc.getFrame();
  while(1)
  {
    //img=cc.getFrame();
    dt.getTrackedRects(img,faces);
    c2g.applyFilter(img,0,vector<Rect>(),img2,scount,smiles);
    sd.applyFilter(img2,faces.size(),faces,img2,scount,smiles);
    for (int i = 0; i < faces.size(); i++)
    {
            	face_i = faces[i];
            	// Make a rectangle around the detected object
            	rectangle(img, face_i, CV_RGB(0, 255,0), 3);
            	if (smiles[i].width>0) rectangle(img, smiles[i], CV_RGB(255,0,0),2);
            	string box_text = string("Tracked Area ")+std::to_string(i);
            	int pos_x = std::max(face_i.x - 10, 0);
            	int pos_y = std::max(face_i.y - 10, 0);
            	// And now put it into the image:
            	putText(img, box_text, Point(pos_x, pos_y), FONT_HERSHEY_SIMPLEX, 1.0, CV_RGB(0,255,0), 2.0);
    }
    if (!img.empty())
    cv::imshow("Detection Based Tracker",img);      // Show the results.
    if(cv::waitKey(10) == 27) break;

  }
  return 0;
}
