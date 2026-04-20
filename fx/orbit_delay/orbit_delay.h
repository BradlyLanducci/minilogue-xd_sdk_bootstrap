#pragma once

//--------------------------------------------------------------------------------

#include "orbit_filter.h"

#include "processors/time_audio_processor.h"
#include "dsp/delay.h"
#include "dsp/sine_lfo.h"
#include "dsp/panner.h"
#include "dsp/butter_filter.h"

#include "osc_api.h"

//--------------------------------------------------------------------------------

class OrbitDelay final : public vlsdk::TimeAudioProcessor
{
public:
    OrbitDelay();

    void processFrame(float &xL, float &xR) override;

    void setDelayTime(float delayTime);
    void setFeedback(float feedback);

private:
    float getNote(float delayTime);
    float calcDelayOffset();

    vlsdk::Delay m_delay;
    vlsdk::Panner m_panner;
    vlsdk::SineLfo m_lfo;
    OrbitFilter m_filter;

    float m_note{ 1.f };
    float m_feedback{ 0.5f };
};

//--------------------------------------------------------------------------------
