#pragma once

#include "vlsdk_dsp/butter_filter.h"
#include "vlsdk_dsp/peaking_filter.h"

//--------------------------------------------------------------------------------

class OrbitFilter
{
public:
    OrbitFilter();

    void processFrame(float &xL, float &xR, float mix);

private:
    void processBehind(float &xL, float &xR);
    void processFront(float &xL, float &xR);

    vlsdk::ButterFilter m_frontHighpass;
    vlsdk::PeakingFilter m_frontMidCarveOut;
    vlsdk::ButterFilter m_behindLowpass;
    vlsdk::PeakingFilter m_behindLowMidBoost;
};

//--------------------------------------------------------------------------------
