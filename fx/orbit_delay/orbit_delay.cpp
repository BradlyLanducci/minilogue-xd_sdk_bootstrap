#include "orbit_delay.h"

#include "fx_api.h"

//--------------------------------------------------------------------------------

OrbitDelay::OrbitDelay(f32pair_t *p_buffer, uint32_t size)
    : m_delay(p_buffer, size)
{
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
