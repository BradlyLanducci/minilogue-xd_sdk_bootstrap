#pragma once

#include "vlsdk.h"

#include "osc_api.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

class DirectFilter
{
public:
    static inline constexpr uint32_t NumCoefficients{ 3 };
    static inline constexpr uint32_t NumChannels{ 2 };
    static inline constexpr float PiDivSr{ M_PI / k_samplerate };

    float (&getNumeratorCoefficients())[NumCoefficients];
    float (&getDenominatorCoefficients())[NumCoefficients];

    void processFrame(float &xL, float &xR);

private:
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
};

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
