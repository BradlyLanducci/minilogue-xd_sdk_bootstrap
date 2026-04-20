#include "orbit_filter.h"

//--------------------------------------------------------------------------------

OrbitFilter::OrbitFilter()
{
    m_frontHighpass.calculateHighpassCoefficients(200.f);

    m_frontMidCarveOut.calculateCoefficients(1000.f);
    m_frontMidCarveOut.setGain(-6.f);

    m_behindLowpass.calculateLowpassCoefficients(5300.f);

    m_behindLowMidBoost.calculateCoefficients(400.f);
    m_behindLowMidBoost.setGain(-6.f);
}

//--------------------------------------------------------------------------------

void OrbitFilter::processFrame(float &xL, float &xR, float mix)
{
    bool inFront{ mix > 0.f };

    float filterLeft;
    float filterRight;

    float frontL{ xL };
    float frontR{ xR };

    float behindL{ xL };
    float behindR{ xR };

    highpass has some kind of issue right now
        // m_frontHighpass.processFrame(frontL, frontR);
        m_frontMidCarveOut.processFrame(frontL, frontR);
    m_behindLowpass.processFrame(behindL, behindR);
    m_behindLowMidBoost.processFrame(behindL, behindR);

    if (inFront)
    {
        filterLeft = frontL;
        filterRight = frontR;
    }
    else
    {
        filterLeft = behindL;
        filterRight = behindR;
    }

    float wet{ std::abs(mix) };
    float dry{ 1.f - wet };

    xL = xL * dry + filterLeft * wet;
    xR = xR * dry + filterRight * wet;
}

//--------------------------------------------------------------------------------
