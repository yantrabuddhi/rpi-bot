#include "histEqualize.h"

histEqualize::histEqualize():filterBase("histogram equalize")
{
    //ctor
}

histEqualize::~histEqualize()
{
    //dtor
}

bool applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions)
{
    out_count=in_count;
    out_regions=in_regions;
    if (in.channels()==1)
        equalizeHist(in,out);
    else
        return false;
    return true;
}
