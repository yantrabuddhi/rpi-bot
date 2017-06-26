/*
  Project: OpenCogER
  File: CamCapture.cpp
  Author: Mandeep Singh Bhatia
  License: AGPL
  Date: May 2017
*/
#include "CamCapture.h"

CamCapture::CamCapture(int width,int height,int cam):w(width),h(height),ccam(cam),running(false)
{
    //ctor
    capture.open(ccam);
    if( capture.isOpened() )
        {
            capture.set(CV_CAP_PROP_FRAME_WIDTH,w);
            capture.set(CV_CAP_PROP_FRAME_HEIGHT,h);
            run = new thread(CamCapture::thread_loop,this);
        }
    else
        {
            cout<<"\nCould not open camera"<<endl;
        }

}

CamCapture::~CamCapture()
{
    //dtor
    running = false;
    run->join();
    delete run;
}

Mat CamCapture::getFrame()
{
    Mat res;
    rd.lock();
    res = current.clone();
    //current.copyTo(res);
    rd.unlock();
    return res;
}

void CamCapture::thread_loop(CamCapture* cc)
{
    cc->running=true;
    while(cc->running)
    {
        cc->rd.lock();
        (cc->capture)>>(cc->current);
        cc->rd.unlock();
        int c = waitKey(10);

    }
}
