#include <gtest/gtest.h>

#include <vlsdk_dsp/butter_filter.h>

#include <random>

//--------------------------------------------------------------------------------

std::vector<f32pair_t> GenerateNoiseVector(size_t size, float db)
{
    float gain{ std::pow(10.f, db / 20.f) };

    std::vector<f32pair_t> noiseVector(size, { 0.f, 0.f });

    std::random_device device;
    std::mt19937 generator{ device() };
    std::uniform_real_distribution<float> dist{ -1.f, 1.f };

    float normalizer{ std::pow(10.f, 4.77f / 20.f) };

    for (size_t s = 0; s < size; s++)
    {
        noiseVector[s] = { gain * normalizer * dist(generator), gain * normalizer * dist(generator) };
    }

    return noiseVector;
}

//--------------------------------------------------------------------------------

float calculateRms(const std::vector<f32pair_t> &samples)
{
    float total{};

    for (const auto &s : samples)
    {
        total += ((s.a * s.a) + (s.b * s.b)) / 2.f;
    }

    return std::sqrt(total / samples.size());
}

//--------------------------------------------------------------------------------

TEST(FilterTests, Stability)
{
    vlsdk::ButterFilter filter;

    filter.calculateHighpassCoefficients(3000.f);

    std::vector<f32pair_t> noiseSamples{ GenerateNoiseVector(k_samplerate, 0.f) };

    for (size_t i = 0; i < noiseSamples.size(); i++)
    {
        f32pair_t s{ noiseSamples[i] };

        filter.processFrame(s.a, s.b);
    }

    float rms{ calculateRms(noiseSamples) };

    ASSERT_TRUE(rms < 1.f);
}

//--------------------------------------------------------------------------------
