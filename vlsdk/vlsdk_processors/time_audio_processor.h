#pragma once

//--------------------------------------------------------------------------------

#include "vlsdk.h"

#include <cstdint>

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

/*
    Base abstract class for delay / reverb audio processing on the Korg Minilogue-XD.
*/
class TimeAudioProcessor
{
public:
    /// @brief Processes a single frame
    /// @param xL Input / output left.
    /// @param xR Input / output right.
    virtual void processFrame(float &xL, float &xR) = 0;

    /// @brief Processes all frames for the provided input and output buffer.
    /// @param p_x The input / output buffer.
    /// @param frames The number of frames to process.
    void processFrames(float *p_x, uint32_t frames);

protected:
    ~TimeAudioProcessor() = default;
};

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
