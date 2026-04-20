#include "dsp/butter_filter.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

ButterFilter::ButterFilter()
{
    calculatePoles();
}

//--------------------------------------------------------------------------------

void ButterFilter::calculatePoles()
{
    std::complex<float> p1{
        { -M_1_SQRT2, M_1_SQRT2 }
    };
    std::complex<float> p2{
        { -M_1_SQRT2, -M_1_SQRT2 }
    };

    std::complex<float> norm{ 1.0, 1.0 };

    norm *= -p1;
    norm *= -p2;

    m_poleNormalizationInv = 1.f / norm.real();
    m_poleAdd = (p1 + p2).real();
    m_poleMult = (p1 * p2).real();
}

//--------------------------------------------------------------------------------

void ButterFilter::calculateLowpassCoefficients(float cutoffFrequency)
{
    float wc{ std::tan(cutoffFrequency * DirectFilter::PiDivSr) };
    float wc2{ wc * wc };

    float Q{ wc / QualityFactor };
    float pAdd{ m_poleAdd * Q };
    float pMul{ m_poleMult * wc2 };

    float (&b)[DirectFilter::NumCoefficients]{ m_directFilter.getNumeratorCoefficients() };
    float (&a)[DirectFilter::NumCoefficients]{ m_directFilter.getDenominatorCoefficients() };

    b[0] = wc2;
    b[1] = 2.f * wc2;
    b[2] = wc2;

    a[0] = -2.f + (2.f * pMul);

    float aIntermediate{ 1.f + pMul };

    float a0{ aIntermediate - pAdd };
    float normalizer{ m_poleNormalizationInv * a0 };
    a[0] = normalizer;

    a[1] = aIntermediate + pAdd;
}

//--------------------------------------------------------------------------------

void ButterFilter::calculateHighpassCoefficients(float cutoffFrequency)
{
    float wc{ std::tan(cutoffFrequency * DirectFilter::PiDivSr) };
    float wc2{ wc * wc };

    float Q{ wc / QualityFactor };
    float pAdd{ m_poleAdd * Q };
    float pMul{ m_poleMult };

    float (&b)[DirectFilter::NumCoefficients]{ m_directFilter.getNumeratorCoefficients() };
    float (&a)[DirectFilter::NumCoefficients]{ m_directFilter.getDenominatorCoefficients() };

    b[0] = 1.f;
    b[1] = -2.f;
    b[2] = 1.f;

    a[1] = (-2.f * pMul) + (2.f * wc2);

    float aIntermediate{ pMul + wc2 };

    float a0{ aIntermediate - pAdd };
    float normalizer{ m_poleNormalizationInv * a0 };
    a[0] = normalizer;

    a[2] = aIntermediate + pAdd;
}

//--------------------------------------------------------------------------------

void ButterFilter::processFrame(float &xL, float &xR)
{
    m_directFilter.processFrame(xL, xR);
}

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
