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
    float wc{ std::tan(cutoffFrequency * PiDivSr) };
    float wc2{ wc * wc };

    float Q{ wc / QualityFactor };
    float pAdd{ m_poleAdd * Q };
    float pMul{ m_poleMult * wc2 };

    float (&b)[NumCoefficients]{ m_coefficients.b };
    float (&a)[NumCoefficients]{ m_coefficients.a };

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
    float wc{ std::tan(cutoffFrequency * PiDivSr) };
    float wc2{ wc * wc };

    float Q{ wc / QualityFactor };
    float pAdd{ m_poleAdd * Q };
    float pMul{ m_poleMult };

    float (&b)[NumCoefficients]{ m_coefficients.b };
    float (&a)[NumCoefficients]{ m_coefficients.a };

    b[0] = 1.f;
    b[1] = 2.f;
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
