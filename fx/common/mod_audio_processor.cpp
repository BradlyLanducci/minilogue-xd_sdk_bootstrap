#include "mod_audio_processor.h"

//--------------------------------------------------------------------------------

void ModAudioProcessor::processFrames(const float *p_x, float *p_y, uint32_t frames)
{
    const float *p_xEnd{ p_x + 2 * frames };

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
