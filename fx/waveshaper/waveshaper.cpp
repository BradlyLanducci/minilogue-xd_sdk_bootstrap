/*
    Created by Bradly Landucci
*/

#include <usermodfx.h>
#include <fx_api.h>

#include <cmath>

//--------------------------------------------------------------------------------

constexpr float DriveRangeDb(100.f);

static float drive{ 0.5f };
static float mix{ 0.5f };

//--------------------------------------------------------------------------------

float waveshape(float in)
{
    return std::tanh(in);
}

//--------------------------------------------------------------------------------

void MODFX_INIT(uint32_t platform, uint32_t api)
{
    (void)platform;
    (void)api;
}

//--------------------------------------------------------------------------------

void MODFX_PROCESS(const float *xn, float *yn, const float *sub_xn, float *sub_yn, uint32_t frames)
{
    static_assert(DriveRangeDb > 1.f);

    (void)sub_xn;
    (void)sub_yn;

    const float *x{ xn };
    const float *xEnd{ xn + 2 * frames };

    float *y{ yn };

    float dry{ 1.f - mix };
    float wet{ mix };

    float currentDrive{ drive * (DriveRangeDb - 1.f) + 1.f };

    for (; x != xEnd; x += 2, y += 2)
    {
        float inLeft{ *x };
        float inRight{ *x + 1 };

        *y = (dry * inLeft) + (wet * waveshape(currentDrive * inLeft));
        *(y + 1) = (inRight) + (wet * waveshape(currentDrive * inRight));
    }
}

//--------------------------------------------------------------------------------

void MODFX_PARAM(uint8_t index, int32_t value)
{
    // Convert fixed-point q31 format to float
    const float valf{ q31_to_f32(value) };
    switch (index)
    {
    case k_user_modfx_param_time:
        drive = valf;
        break;
    case k_user_modfx_param_depth:
        mix = valf;
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------------------------
