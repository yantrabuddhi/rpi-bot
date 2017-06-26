#include "color2gray.h"

color2gray::color2gray():filterBase("color2gray")
{
    //ctor
}

color2gray::~color2gray()
{
    //dtor
}

bool applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions)
{
    out_count=in_count;
    out_regions=in_regions;
    if (in.channels()>1)
        cvtColor(in,out,CV_BGR2GRAY);
    else
        out=in;
    return true;
}
