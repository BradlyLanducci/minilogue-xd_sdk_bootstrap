#pragma once

//--------------------------------------------------------------------------------

#include "vlsdk.h"
#include "processors/time_audio_processor.h"
#include "dsp/delay.h"

#include "osc_api.h"

//--------------------------------------------------------------------------------

class OrbitDelay : public vlsdk::TimeAudioProcessor
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

    float m_note{ 1.f };
    float m_feedback{ 0.5f };
};

//--------------------------------------------------------------------------------
