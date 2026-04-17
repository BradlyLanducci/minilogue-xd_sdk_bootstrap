#include "orbit_delay.h"

#include "fx_api.h"

//--------------------------------------------------------------------------------

constexpr uint32_t GetDelaySize(float maxNote, float minBpm)
{
    return vlsdk::nextPow2U32(4.f * static_cast<uint32_t>((60.f / minBpm) * (k_samplerate * maxNote)));
}

//--------------------------------------------------------------------------------

constexpr float MinNote{ 1.f / 64.f };
constexpr float MaxNote{ 0.5f };

/// @brief Minimum bpm of the Korg Minilogue-XD.
constexpr float MinBpm{ 56.f };
constexpr uint32_t MaxDelaySamples{ GetDelaySize(MaxNote, MinBpm) };

//--------------------------------------------------------------------------------

OrbitDelay::OrbitDelay()
    : m_delay(MaxDelaySamples)
{
    m_lfo.setFrequency(5.f);
}

//--------------------------------------------------------------------------------

void OrbitDelay::processFrame(float &xL, float &xR)
{
    f32pair_t samplePair{ m_delay.readFrac(calcDelayOffset()) };

    f32pair_t feedbackPair{ m_feedback * samplePair.a, m_feedback * samplePair.b };

    m_delay.write({ feedbackPair.a + xL, feedbackPair.b + xR });

    xL += samplePair.a;
    xR += samplePair.b;

    // Apply orbital effect
    // Update pan & filter
    float lfoCycle{ m_lfo.getNextCycle() };
    m_panner.setPan(lfoCycle / 2.f + 0.5f);
    m_panner.processFrame(xL, xR);
}

//--------------------------------------------------------------------------------

void OrbitDelay::setDelayTime(float delayTime)
{
    // Normalize to a quarter note == 1.f.
    m_note = 4.f * getNote(delayTime);
}

//--------------------------------------------------------------------------------

void OrbitDelay::setFeedback(float feedback)
{
    m_feedback = feedback;
}

//--------------------------------------------------------------------------------

float OrbitDelay::getNote(float delayTime)
{
    return MinNote + (delayTime * (MaxNote - MinNote));
}

//--------------------------------------------------------------------------------

float OrbitDelay::calcDelayOffset()
{
    float bpm{ fx_get_bpmf() };

    return m_note * ((60.f / bpm) * k_samplerate);
}

//--------------------------------------------------------------------------------
