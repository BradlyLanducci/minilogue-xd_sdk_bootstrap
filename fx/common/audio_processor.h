#pragma once

//--------------------------------------------------------------------------------

#include <cstdint>

//--------------------------------------------------------------------------------

/*
    Base abstract class for audio processing on the Korg Minilogue-XD.

    It's okay to do inheritance here because this object is not constructable thus
    we do not need a virtual destructor.
*/
class AudioProcessor
{
public:
    void updatePointers(const float *p_x, float *p_y = nullptr);

    virtual void processFrame(const float xL, const float xR, float &yL, float &yR) = 0;

    void processFrames(uint32_t frames);

private:
    const float *mp_x{ nullptr };
    float *mp_y{ nullptr };
};

//--------------------------------------------------------------------------------
