#ifndef HISTEQUALIZE_H
#define HISTEQUALIZE_H

#include <filterBase.h>


class histEqualize : public filterBase
{
    public:
        histEqualize();
        virtual ~histEqualize();
        virtual bool applyFilter(Mat in,unsigned int in_count,vector<Rect> in_regions,Mat& out,unsigned int& out_count,vector<Rect>& out_regions);
    protected:
    private:
};

#endif // HISTEQUALIZE_H
