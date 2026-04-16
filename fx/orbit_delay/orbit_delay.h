#pragma once

//--------------------------------------------------------------------------------

#include "time_audio_processor.h"

#include "DelayLine.hpp"
#include "osc_api.h"

//--------------------------------------------------------------------------------
/*
    Stealing this from their code, so I can make it constexpr.

    This is a weird hack to get around C++11 constexpr not supporting local variables.
*/
constexpr uint32_t nextPow2U32(uint32_t x)
{
    return (x <= 1) ? 1 : (x--, x |= x >> 1, x |= x >> 2, x |= x >> 4, x |= x >> 8, x |= x >> 16, x + 1);
}

//--------------------------------------------------------------------------------

constexpr uint32_t GetDelaySize(float maxNote, float minBpm)
{
    return nextPow2U32(static_cast<uint32_t>((minBpm / 60.f) * (k_samplerate * maxNote)));
}

//--------------------------------------------------------------------------------

constexpr float MinNote{ 1.f / 32.f };
constexpr float MaxNote{ 1.f };
constexpr float MinBpm{ 55.f };
constexpr uint32_t MaxDelaySamples{ GetDelaySize(MaxNote, MinBpm) };

//--------------------------------------------------------------------------------

class OrbitDelay : public TimeAudioProcessor
{
public:
    explicit OrbitDelay(f32pair_t *p_buffer, uint32_t size);

    void processFrame(float &xL, float &xR) override;

    void setDelayTime(float delayTime);
    void setFeedback(float feedback);

private:
    float getNote(float delayTime);
    float calcDelayOffset();

    dsp::DualDelayLine m_delay;

    float m_note{};
    float m_feedback{ 0.5f };
};

//--------------------------------------------------------------------------------
