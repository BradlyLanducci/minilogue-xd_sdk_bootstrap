#pragma once

//--------------------------------------------------------------------------------

#include "vlsdk.h"

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

    const uint32_t NumCoefficients{ 3 };
    const uint32_t NumChannels{ 2 };

    struct
    {
        float b[NumCoefficients]{};
        float a[NumCoefficients]{};
    } m_coefficients;

    struct
    {
        float x[NumCoefficients]{};
        float y[NumCoefficients]{};
    } m_history[NumChannels];

    const float QualityFactor{ M_1_SQRT2 };
    const float PiDivSr{ M_PI / k_samplerate };

    float m_poleNormalizationInv{ 1.f };
    float m_poleAdd{};
    float m_poleMult{};
};

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
