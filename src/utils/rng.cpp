#include "rng.hpp"

#include <chrono>

RNG::RNG()
    : m_Engine(std::random_device{}()), m_NormalDistribution(0.0, 1.0)
{
    unsigned int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    Seed(seed);  // There will be only one see
}

RNG& RNG::GetRNG() {
    static RNG rngInstance;
    return rngInstance;
}

int RNG::GetNextInt(int min, int max) {
    std::uniform_int_distribution<int> _distribution(min, max);
    return _distribution(m_Engine);
}

float RNG::GetNextFloat(float min, float max) {
    std::uniform_real_distribution<float> _distribution(min, max);
    return _distribution(m_Engine);
}
