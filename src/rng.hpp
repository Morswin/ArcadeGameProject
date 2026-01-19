#ifndef RNG_H
#define RNG_H

#include <random>

class RNG {
private:
    std::mt19937 m_Engine;
    std::normal_distribution<double> m_NormalDistribution;
public:
    RNG(const RNG&) = delete;
    RNG& operator=(const RNG&) = delete;

    static RNG& GetRNG();
    int GetNextInt(int min, int max);

    inline void Seed(int seed) { m_Engine.seed(seed); }
    inline double GetNextNormal() { return m_NormalDistribution(m_Engine); }
    inline std::mt19937& GetRNGEngine() { return m_Engine; }
private:
    RNG();
};

#endif  // RNG_H
