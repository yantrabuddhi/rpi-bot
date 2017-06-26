#include "faceDetect.h"

faceDetect::faceDetect():filterBase("human face detect")
{
    //ctor
    string face_cascade_name = "haarcascade_frontalface_alt.xml";
    if( !face_cascade.load( face_cascade_name ) ){ cout<<"--(!)Error loading face cascade xml\n"; return; };
}

faceDetect::~faceDetect()
{
    //dtor
}

bool faceDetect::applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions)
{
    face_cascade.detectMultiScale( in, out_regions, 1.1, 4, 0|CV_HAAR_SCALE_IMAGE, Size(55, 55) );
    out_count=out_regions.size();
    out=in;
    return true;
}
