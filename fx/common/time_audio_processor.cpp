#include "time_audio_processor.h"

//--------------------------------------------------------------------------------

void TimeAudioProcessor::processFrames(float *p_x, uint32_t frames)
{
    const float *p_xEnd{ p_x + 2 * frames };

    for (; p_x != p_xEnd; p_x += 2)
    {
        float &xL{ *p_x };
        float &xR{ *(p_x + 1) };

        processFrame(xL, xR);
    }
}

//--------------------------------------------------------------------------------
