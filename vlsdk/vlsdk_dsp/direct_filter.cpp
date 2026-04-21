#include "vlsdk_dsp/direct_filter.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

float (&DirectFilter::getNumeratorCoefficients()) [NumCoefficients] { return m_coefficients.b; }

//--------------------------------------------------------------------------------

float (&DirectFilter::getDenominatorCoefficients()) [NumCoefficients] { return m_coefficients.a; }

//--------------------------------------------------------------------------------

void DirectFilter::processFrame(float &xL, float &xR)
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
