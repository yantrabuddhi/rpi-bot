/*
  Project: OpenCogER
  File: CamCapture.h
  Author: Mandeep Singh Bhatia
  License: AGPL
  Date: May 2017
*/
#ifndef CAMCAPTURE_H
#define CAMCAPTURE_H


#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <cstdio>
#include <thread>
#include <mutex>

using namespace std;
using namespace cv;

class CamCapture
{
    public:
        CamCapture(int width=320;int height=240;int cam = -1);
        virtual ~CamCapture();
        Mat getFrame();//Mat is like shared_ptr, make deep copy here and use mutex
    protected:
    private:
        int w,h;
        int ccam;
        Mat current;
        VideoCapture capture;
        bool running;
        static void thread_loop(CamCapture* cc);
        thread* run;
        mutex rd;
};

#endif // CAMCAPTURE_H
