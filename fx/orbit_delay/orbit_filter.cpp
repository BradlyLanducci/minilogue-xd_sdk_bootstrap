#include "orbit_filter.h"

//--------------------------------------------------------------------------------

OrbitFilter::OrbitFilter()
{
    m_frontHighpass.calculateHighpassCoefficients(2000.f);

    m_frontMidCarveOut.calculateCoefficients(1000.f);
    m_frontMidCarveOut.setGain(-6.f);

    m_behindLowpass.calculateLowpassCoefficients(3000.f);

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

    m_frontHighpass.processFrame(frontL, frontR);
    // m_frontMidCarveOut.processFrame(frontL, frontR);
    m_behindLowpass.processFrame(behindL, behindR);
    // m_behindLowMidBoost.processFrame(behindL, behindR);

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

    xL = xL * dry * 0.5f + filterLeft * wet;
    xR = xR * dry * 0.5f + filterRight * wet;
}

//--------------------------------------------------------------------------------
