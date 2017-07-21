#ifndef DETECTIONTRACKERBASE_H
#define DETECTIONTRACKERBASE_H

#include "CamCapture.h"

#include "opencv2/contrib/detection_based_tracker.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;
using namespace cv;

class DetectionTrackerBase
{
    public://efficient use for face or object cascade only
        DetectionTrackerBase(string det_name,string casc_file, CamCapture* ccap);
        inline string getName(){return name;}
        void run();
        void stop();
        inline bool running(){return isRunning;}
        void getTrackedRects(vector<Rect>& rects);
        //bool getTrackedRects(vector<Rect>& rects,vector<int>& id);
        virtual ~DetectionTrackerBase();
    protected:
    private:
    string name;
    string cascadeFile;
    CamCapture* cc;
    bool isRunning;
    thread* rn;
    //vector<Rect>prevRects;
    //vector<int>prevIds;
    vector<Rect>currRects;
    mutex rd;
    //vector<int>currIds;
    static void track(DetectionTrackerBase* th);
    DetectionBasedTracker::Parameters param;
    DetectionBasedTracker* obj;
    /*
    bool point_in_rect(int x,int y,Rect rct);
    bool rects_overlap(Rect rct1, Rect rct2);
    void update_ids();
    */
}; //run in a thread and pass function for image capture

#endif // DETECTIONTRACKERBASE_H
