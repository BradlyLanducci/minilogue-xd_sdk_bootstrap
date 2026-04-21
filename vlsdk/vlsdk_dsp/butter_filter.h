#pragma once

//--------------------------------------------------------------------------------

#include "vlsdk_dsp/direct_filter.h"

#include <utility>
#include <complex>
#include "osc_api.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

class ButterFilter
{
public:
    ButterFilter();

    void calculateLowpassCoefficients(float cutoffFrequency);
    void calculateHighpassCoefficients(float cutoffFrequency);

    void processFrame(float &xL, float &xR);

private:
    void calculatePoles();

    const float QualityFactor{ M_1_SQRT2 };

    DirectFilter m_directFilter;

    float m_poleAdd{};
    float m_poleMult{};
};

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
