#include "waveshaper.h"

#include <cmath>

//--------------------------------------------------------------------------------

void Waveshaper::processFrame(const float xL, const float xR, float &yL, float &yR)
{
    float dry{ 1.f - m_mix };
    float wet{ m_mix };

    yL = (dry * xL) + (wet * waveshape(xL));
    yR = (dry * xR) + (wet * waveshape(xR));
}

//--------------------------------------------------------------------------------

void Waveshaper::setMix(float mix)
{
    m_mix = mix;
}

//--------------------------------------------------------------------------------

void Waveshaper::setDrive(float drive)
{
    m_drive = drive;
}

//--------------------------------------------------------------------------------

void Waveshaper::setDriveRange(float driveRange)
{
    m_driveRange = std::fmax(driveRange, 1.f);
}

//--------------------------------------------------------------------------------

float Waveshaper::waveshape(float x)
{
    float drive{ (m_drive * (m_driveRange - 1.f)) + 1.f };
    float dist{ std::tanh(drive * x) };

    /*
        Empirically found that 0.25 seems to be an okay scalar to ensure we don't
        get too much gain :)
    */
    float scalar{ 1.f + (0.25f - 1.f) * m_drive };

    return scalar * dist;
}

//--------------------------------------------------------------------------------