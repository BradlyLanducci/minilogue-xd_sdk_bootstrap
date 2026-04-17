#include "dsp/stereo_panner.h"

#include "float_math.h"
#include <cmath>

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

void StereoPanner::setPan(float pan)
{
    m_pan = pan;
}

//--------------------------------------------------------------------------------

void StereoPanner::processFrame(float &xL, float &xR)
{
    xL = std::cos(m_pan * M_PI / 2.f) * xL;
    xR = std::sin(m_pan * M_PI / 2.f) * xR;
}

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------