#ifndef COLOR2GRAY_H
#define COLOR2GRAY_H

#include <filterBase.h>


class color2gray : public filterBase
{
    public:
        color2gray();
        virtual ~color2gray();
        virtual bool applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions);
    protected:
    private:
};

#endif // COLOR2GRAY_H
