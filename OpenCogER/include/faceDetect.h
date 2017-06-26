#ifndef FACEDETECT_H
#define FACEDETECT_H

#include <filterBase.h>


class faceDetect : public filterBase
{
    public:
        faceDetect();
        virtual ~faceDetect();
        virtual bool applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions);
    protected:
    private:
};

#endif // FACEDETECT_H
