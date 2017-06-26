#ifndef SMILEDETECT_H
#define SMILEDETECT_H

#include <filterBase.h>


class smileDetect : public filterBase
{
    public:
        smileDetect();
        virtual ~smileDetect();
        virtual bool applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions);
    protected:
    private:
    CascadeClassifier smile_cascade;
};

#endif // SMILEDETECT_H
