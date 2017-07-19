#include "DetectionTrackerBase.h"

DetectionTrackerBase::DetectionTrackerBase(string det_name,string casc_file, CamCapture* ccap):name(det_name),cascadeFile(casc_file),cc(ccap),isRunning(false)
{
    //ctor
    param.maxObjectSize = 240;//400
    param.maxTrackLifetime = 20;
    param.minDetectionPeriod = 7;
    param.minNeighbors = 3;
    param.minObjectSize = 50;//20
    param.scaleFactor = 1.1;
    obj=DetectionBasedTracker(cascadeFile,param);
}

DetectionTrackerBase::~DetectionTrackerBase()
{
    //dtor
    stop();
}

void DetectionTrackerBase::run()
{
    if (isRunning) return;
    obj.run();
    isRunning = true;
    rn = new thread(DetectionTrackerBase::track(),this);
}

void DetectionTrackerBase::stop()
{
    if (isRunning)
    {
        isRunning = false;
        rn->join();
    }
}

/*
bool DetectionTrackerBase::point_in_rect(int x, int y, Rect rct)
{
    return (x>=rct.x && x<=rct.x+rct.width && y>=rct.y && y<=rct.y+rct.height);
}

bool DetectionTrackerBase::rects_overlap(Rect rct1, Rect rct2)
{
    return (point_in_rect(rct1.x,rct1.y,rct2)
            || point_in_rect(rct1.x+rct1.width,rct1.y,rct2)
            || point_in_rect(rct1.x,rct1.y+rct1.height,rct2)
            || point_in_rect(rct1.x+rct1.width,rct1.y+rct1.height,rct2));
}

void DetectionTrackerBase::update_ids()
{

   for (int i=0;i<currRects.size();i++)
   {
        double dist=320.0;
        const double thresh_dist=30;
        int closest_id = i;
        for (int j=0;j<prevRects.size();j++)
        {
        }
   }

}
*/
void DetectionTrackerBase::track()
{
    Mat in,out;
    while (isRunning)
    {
        in = cc->getFrame();
        cvtColor(in,out,COLOR_BGR2GRAY);
        obj.process(out);
        rd.lock();
        obj.getObjects(currRects);
        rd.unlock();
        //update_ids();
    }
    obj.stop();
}

void DetectionTrackerBase::getTrackedRects(vector<Rect>& rects)
{
   rd.lock();
   rects=currRects;
   rd.unlock();
}

