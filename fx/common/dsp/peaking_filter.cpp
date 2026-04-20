#include "dsp/peaking_filter.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

void PeakingFilter::calculateCoefficients(float cutoffFrequency)
{
    float wc{ std::tan(cutoffFrequency * PiDivSr) };
    float wc2{ wc * wc };

    float Q{ wc / QualityFactor };
    float R{ std::sqrt(m_gain) * Q };

    float (&b)[NumCoefficients]{ m_coefficients.b };
    float (&a)[NumCoefficients]{ m_coefficients.a };

    b[0] = 1.f + R + wc2;
    b[1] = -2.f + 2.f * wc2;
    b[2] = 1.f - R + wc2;

    float a0Inv{ 1.f / (1.f + Q + wc2) };
    a[0] = a0Inv;
    a[1] = -2.f + 2.f * wc2;
    a[2] = 1.f - Q + wc2;
}

//--------------------------------------------------------------------------------

void PeakingFilter::setGain(float gain)
{
    m_gain = std::pow(10.f, gain / 10.f);
}

//--------------------------------------------------------------------------------

void PeakingFilter::processSample(float &xL, float &xR)
{
    float (&b)[NumCoefficients]{ m_coefficients.b };
    float (&a)[NumCoefficients]{ m_coefficients.a };

    float (&hxL)[NumCoefficients]{ m_history[0].x };
    float (&hyL)[NumCoefficients]{ m_history[0].y };
    float (&hxR)[NumCoefficients]{ m_history[1].x };
    float (&hyR)[NumCoefficients]{ m_history[1].y };

    hxL[0] = xL;
    hxR[0] = xR;

    hyL[0] = a[0] * (b[0] * hxL[0] + b[1] * hxL[1] + b[2] * hxL[2] - a[1] * hyL[1] - a[2] * hyL[2]);
    hxL[2] = hxL[1];
    hxL[1] = hxL[0];
    hyL[2] = hyL[1];
    hyL[1] = hyL[0];

    hyR[0] = a[0] * (b[0] * hxR[0] + b[1] * hxR[1] + b[2] * hxR[2] - a[1] * hyR[1] - a[2] * hyR[2]);
    hxR[2] = hxR[1];
    hxR[1] = hxR[0];
    hyR[2] = hyR[1];
    hyR[1] = hyR[0];

    xL = hyL[0];
    xR = hyR[0];
}

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
