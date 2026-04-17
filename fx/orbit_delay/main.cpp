/*
    Created by Bradly Landucci
*/

#include "orbit_delay.h"

#include "userdelfx.h"

//--------------------------------------------------------------------------------

static OrbitDelay orbitDelay;

//--------------------------------------------------------------------------------

void DELFX_PROCESS(float *xn, uint32_t frames)
{
    orbitDelay.processFrames(xn, frames);
}

//--------------------------------------------------------------------------------

void DELFX_PARAM(uint8_t index, int32_t value)
{
    // Convert fixed-point q31 format to float
    float v{ q31_to_f32(value) };
    switch (index)
    {
    case k_user_delfx_param_time:
        orbitDelay.setDelayTime(v);
        break;
    case k_user_delfx_param_depth:
        orbitDelay.setFeedback(v);
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------------------------
