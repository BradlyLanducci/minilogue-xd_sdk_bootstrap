#include "vlsdk_processors/time_audio_processor.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

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

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
