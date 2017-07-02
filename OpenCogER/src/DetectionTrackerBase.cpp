#include "DetectionTrackerBase.h"

DetectionTrackerBase::DetectionTrackerBase(string det_name,string casc_file, CamCapture* ccap):name(det_name),cascadeFile(casc_file),cc(ccap),isRunning(false)
{
    //ctor
}

DetectionTrackerBase::~DetectionTrackerBase()
{
    //dtor
}
