/*
    Created by Bradly Landucci
*/

#include "orbit_delay.h"

//--------------------------------------------------------------------------------

constexpr uint32_t RamSize{ 192000 };
static f32pair_t DelayRam[RamSize] __sdram;

//--------------------------------------------------------------------------------

static OrbitDelay orbitDelay{ DelayRam, RamSize };

//--------------------------------------------------------------------------------

void DELFX_INIT(uint32_t platform, uint32_t api)
{
    (void)platform;
    (void)api;
}

//--------------------------------------------------------------------------------

void DELFX_PROCESS(float *xn, uint32_t frames)
{
}

//--------------------------------------------------------------------------------

void DELFX_PARAM(uint8_t index, int32_t value)
{
    // Convert fixed-point q31 format to float
    const float valf{ q31_to_f32(value) };
    switch (index)
    {
    case k_user_delfx_param_time:
        break;
    case k_user_delfx_param_depth:
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------------------------
