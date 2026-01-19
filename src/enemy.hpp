#ifndef ENEMY_H
#define ENEMY_H

#include "entity.hpp"
#include "player.hpp"

class Enemy : public Entity
{
private:
    double m_DetectionRange = 3.0;
public:
    Enemy(int spriteColumn, int spriteRow);
    ~Enemy() noexcept;

    void WanderAround(float deltaTime);
    void FollowPlayer(float deltaTime, const Player& player);

    inline bool IsProvoked(const Player& player) const { return glm::distance(GetPosition(), player.GetPosition()) < m_DetectionRange; }
    inline double GetDetectionRange() const { return m_DetectionRange; }
};

#endif //ENEMY_H
