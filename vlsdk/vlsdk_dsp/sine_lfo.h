#pragma once

//--------------------------------------------------------------------------------

#include "vlsdk.h"

#include "osc_api.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

class SineLfo
{
public:
    void setPhase(float radians);
    void setFrequency(float frequency);

    float getNextCycle();

private:
    float m_time{};
    const float m_timeIncrement{ k_samplerate_recipf };
    float m_phase{};
    float m_frequency{ 1.f };
};

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
