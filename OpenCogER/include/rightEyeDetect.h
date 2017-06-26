#ifndef RIGHTEYEDETECT_H
#define RIGHTEYEDETECT_H

#include <filterBase.h>


class rightEyeDetect : public filterBase
{
    public:
        rightEyeDetect();
        virtual ~rightEyeDetect();
        virtual bool applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions);
    protected:
    private:
    CascadeClassifier eye_cascade;
};

#endif // RIGHTEYEDETECT_H
