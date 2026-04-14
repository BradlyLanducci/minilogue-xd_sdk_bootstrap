/*
    Created by Bradly Landucci
*/

#include <usermodfx.h>

#include "waveshaper.h"

//--------------------------------------------------------------------------------

constexpr float DriveRange(100.f);

//--------------------------------------------------------------------------------

static Waveshaper waveshaper;

//--------------------------------------------------------------------------------

void MODFX_INIT(uint32_t platform, uint32_t api)
{
    (void)platform;
    (void)api;

    waveshaper.setDriveRange(DriveRange);
}

//--------------------------------------------------------------------------------

void MODFX_PROCESS(const float *xn, float *yn, const float *sub_xn, float *sub_yn, uint32_t frames)
{
    waveshaper.updatePointers(xn, yn);
    waveshaper.processFrames(frames);
}

//--------------------------------------------------------------------------------

void MODFX_PARAM(uint8_t index, int32_t value)
{
    // Convert fixed-point q31 format to float
    const float valf{ q31_to_f32(value) };
    switch (index)
    {
    case k_user_modfx_param_time:
        waveshaper.setDrive(valf);
        break;
    case k_user_modfx_param_depth:
        waveshaper.setMix(valf);
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------------------------
