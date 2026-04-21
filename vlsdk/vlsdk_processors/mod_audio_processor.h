#pragma once

//--------------------------------------------------------------------------------

#include "vlsdk.h"

#include <cstdint>

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

/*
    Base abstract class for modulator audio processing on the Korg Minilogue-XD.
*/
class ModAudioProcessor
{
public:
    /// @brief Processes a single frame
    /// @param xL Input left.
    /// @param xR Input right.
    /// @param yL Output left.
    /// @param yR Output right.
    virtual void processFrame(const float xL, const float xR, float &yL, float &yR) = 0;

    /// @brief Processes all frames for the provided input and output buffer.
    /// @param p_x The input buffer.
    /// @param p_y The output buffer.
    /// @param frames The number of frames to process.
    void processFrames(const float *p_x, float *p_y, uint32_t frames);

protected:
    ~ModAudioProcessor() = default;
};

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
