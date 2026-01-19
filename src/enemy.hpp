#ifndef ENEMY_H
#define ENEMY_H

#include "entity.hpp"
#include "player.hpp"

class Enemy : public Entity
{
private:
    double m_DetectionRange{3.0};
    float m_WanderSpeed{0.25f};
    float m_WanderCounter{10.0f};  // For tracking delays between wandering direction changes. It should be set to more than m_WanderCounterTarget, so the first decision about the direction change happens at the beginning of the game, not after the first fill up of the counter.
    float m_WanderCounterTarget{0.5f};  // How often those changes will occur in seconds
    float m_ChaseSpeed{0.6f};
public:
    Enemy(int spriteColumn, int spriteRow);
    ~Enemy() noexcept;

    void Simulate(float deltaTime, const std::map<MapPosition, unsigned int>& mapData, const Player& player);
    void WanderAround(float deltaTime);
    void ChasePlayer(float deltaTime, const Player& player);

    inline bool IsProvoked(const Player& player) const { return glm::distance(GetPosition(), player.GetPosition()) < m_DetectionRange; }
    inline double GetDetectionRange() const { return m_DetectionRange; }
};

#endif //ENEMY_H
