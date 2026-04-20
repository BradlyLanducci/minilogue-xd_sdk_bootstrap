#include "dsp/peaking_filter.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

void PeakingFilter::calculateCoefficients(float cutoffFrequency)
{
    float wc{ std::tan(cutoffFrequency * DirectFilter::PiDivSr) };
    float wc2{ wc * wc };

    float Q{ wc / QualityFactor };
    float R{ std::sqrt(m_gain) * Q };

    float (&b)[DirectFilter::NumCoefficients]{ m_directFilter.getNumeratorCoefficients() };
    float (&a)[DirectFilter::NumCoefficients]{ m_directFilter.getDenominatorCoefficients() };

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

void PeakingFilter::processFrame(float &xL, float &xR)
{
    m_directFilter.processFrame(xL, xR);
}

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
