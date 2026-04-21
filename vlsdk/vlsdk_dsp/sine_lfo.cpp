#include "vlsdk_dsp/sine_lfo.h"

#include <cmath>

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

void SineLfo::setPhase(float radians)
{
    m_phase = radians;
}

//--------------------------------------------------------------------------------

void SineLfo::setFrequency(float frequency)
{
    m_frequency = frequency;
}

//--------------------------------------------------------------------------------

float SineLfo::getNextCycle()
{
    float cycle{ std::sin(m_frequency * m_time + m_phase) };

    m_time += m_timeIncrement;

    if (m_time >= M_TWOPI)
    {
        m_time = std::fmod(m_time, M_TWOPI);
    }

    return cycle;
}

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
