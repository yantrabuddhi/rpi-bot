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
    public:
        DetectionTrackerBase(string det_name,string casc_file, CamCapture* ccap);
        inline string getName(){return name;}
        void run();
        inline bool running(){return isRunning;}
        inline string getName(){return name;}
        bool getTrackedRects(vector<Rect>& rects,vector<int>& id);
        virtual ~DetectionTrackerBase();
    protected:
    private:
    string name;
    string cascadeFile;
    CamCapture* cc;
    bool isRunning;
    DetectionBasedTracker* dt;
    vector<Rect>currRects;
    vector<int>currIds;
    void track();
}; //run in a thread and pass function for image capture

#endif // DETECTIONTRACKERBASE_H
