#pragma once

//--------------------------------------------------------------------------------

#include "dsp/direct_filter.h"

#include "osc_api.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

class PeakingFilter
{
public:
    void calculateCoefficients(float cutoffFrequency);

    void setGain(float gain);

    void processFrame(float &xL, float &xR);

private:
    const float QualityFactor{ M_1_SQRT2 };

    DirectFilter m_directFilter;

    /// @brief Amplitude gain
    float m_gain{ 1.f };
};

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
