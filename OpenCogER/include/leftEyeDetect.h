#ifndef LEFTEYEDETECT_H
#define LEFTEYEDETECT_H

#include <filterBase.h>


class leftEyeDetect: public filterBase
{
    public:
        leftEyeDetect();
        virtual ~leftEyeDetect();
        virtual bool applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions);
    protected:
    private:
    CascadeClassifier eye_cascade;
};

#endif // LEFTEYEDETECT_H
