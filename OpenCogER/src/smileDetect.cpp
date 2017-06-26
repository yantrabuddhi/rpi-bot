#include "smileDetect.h"

smileDetect::smileDetect():filterBase("human smile detect")
{
    //ctor
    string smile_cascade_name = "haarcascade_smile.xml";
    if( !smile_cascade.load( smile_cascade_name ) ){ cout<<"--(!)Error loading smile cascade xml\n"; return; };
}

smileDetect::~smileDetect()
{
    //dtor
}
//input faces
bool smileDetect::applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions)
{
    Mat roi;
    out_count=0;
    out_regions.clear();
    for (int i=0;i<in_count;i++)
    {
        vector<Rect>res;
        roi=in(in_regions[i]);
        smile_cascade.detectMultiScale( roi, res, 1.7, 8, 0|CV_HAAR_SCALE_IMAGE, Size(25, 25) );
        for (int j=0;j<res.size();j++)
        {
            out_regions.push_back(res[j]);
        }
    }
    out_count=out_regions.size();
    out=in;
    return true;
}
