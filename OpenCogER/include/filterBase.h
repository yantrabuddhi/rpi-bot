#ifndef FILTERBASE_H
#define FILTERBASE_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>
#include <memory>//shared_ptr

using namespace std;
using namespace cv;

class filterBase
{
    public:
        filterBase(string filtername);
        virtual ~filterBase();
        inline string getFilterName(){return filterName};
        virtual bool applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions)=0;
    protected:
    private:
    string filterName;
};

#endif // FILTERBASE_H
