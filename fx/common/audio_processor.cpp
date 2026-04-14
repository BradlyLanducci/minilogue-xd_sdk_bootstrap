#include "audio_processor.h"

//--------------------------------------------------------------------------------

void AudioProcessor::updatePointers(const float *p_x, float *p_y)
{
    mp_x = p_x;
    mp_y = p_y;
}

//--------------------------------------------------------------------------------

void AudioProcessor::processFrames(uint32_t frames)
{
    const float *p_x{ mp_x };
    const float *p_xEnd{ mp_x + 2 * frames };

    float *p_y{ mp_y };

    for (; p_x != p_xEnd; p_x += 2, p_y += 2)
    {
        const float xL{ *p_x };
        const float xR{ *(p_x + 1) };

        float &yL{ *p_y };
        float &yR{ *(p_y + 1) };

        processFrame(xL, xR, yL, yR);
    }
}

//--------------------------------------------------------------------------------
