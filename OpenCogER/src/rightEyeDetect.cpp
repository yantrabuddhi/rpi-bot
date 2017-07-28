#include "rightEyeDetect.h"

rightEyeDetect::rightEyeDetect():filterBase("human right eye")
{
    //ctor
    string eye_cascade_name = "haarcascade_righteye_2splits.xml";
    if( !eye_cascade.load( eye_cascade_name ) ){ cout<<"--(!)Error loading right eye cascade xml\n"; return; };
}

rightEyeDetect::~rightEyeDetect()
{
    //dtor
}

bool rightEyeDetect::applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions)
{
    Mat roi;
    out_count=0;
    out_regions.clear();
    for (int i=0;i<in_count;i++)
    {
        vector<Rect>res;
        roi=in(in_regions[i]);
        eye_cascade.detectMultiScale( roi, res, 1.7, 8, 0|CV_HAAR_SCALE_IMAGE, Size(25, 25) );
        if (res.size()<1) out_regions.push_back(Rect(0,0,0,0));
        else out_regions.push_back(Rect(in_regions[i].x+res[0].x,in_regions[i].y+res[0].y,res[0].width,res[0].height));
    }
    out_count=out_regions.size();
    out=in;
    return true;
}
