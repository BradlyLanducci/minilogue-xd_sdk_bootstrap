#pragma once

#include "vlsdk.h"

#include "osc_api.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

class PeakingFilter
{
public:
    void calculateCoefficients(float cutoffFrequency);

    void setGain(float gain);

    void processSample(float &xL, float &xR);

private:
    const float QualityFactor{ M_1_SQRT2 };
    const float PiDivSr{ M_PI / k_samplerate };

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

    /// @brief Amplitude gain
    float m_gain{ 1.f };
};

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
