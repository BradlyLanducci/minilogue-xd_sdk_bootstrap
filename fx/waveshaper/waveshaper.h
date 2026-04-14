#pragma once

//--------------------------------------------------------------------------------

#include "audio_processor.h"

#include <cstdint>

//--------------------------------------------------------------------------------

/*
    Waveshapes audio with a simple tanh function.
*/
class Waveshaper : public AudioProcessor
{
public:
    /// @brief Processes a single frame of audio for a L/R channel.
    /// @param xL Input left.
    /// @param xR Input right.
    /// @param yL Output left to be calculated.
    /// @param yr Output right to be calculated.
    void processFrame(const float xL, const float xR, float &yL, float &yR) override;

    /// @brief How much of this signal will be waveshaped vs dry.
    /// @param mix How much should be "wet".
    void setMix(float mix);

    /// @brief Sets the current drive scalar. Note: You must intitialize drive range first..
    /// @param drive A 0 to 1 value to be mapped to the internal drive range.
    void setDrive(float drive);

    /// @brief Sets the drive multiplier.
    /// @param driveRange The drive scalar. Note: This must be >= 1.f.
    void setDriveRange(float driveRange);

private:
    float waveshape(float x);

    float m_mix{ 1.f };
    float m_drive{ 1.f };
    float m_driveRange{ 1.f };
};

//--------------------------------------------------------------------------------
