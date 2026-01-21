#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.hpp"

class Projectile : public Entity
{
private:
    double m_Lifespan{4.0};
    double m_CurrentLife{0.0};
    bool m_HasHit{false};
    int m_ProjectileDamage{10};
public:
    Projectile(int spriteColumn, int spriteRow);
    ~Projectile() noexcept;

    void Simulate(float deltaTime, const std::map<MapPosition, unsigned int>& mapData);

    inline void OnHitEnemy() { m_HasHit = true; }
    inline bool ReadyForDeletion() const { return m_CurrentLife >= m_Lifespan || m_HasHit; }
    inline int GetDamage() const { return m_ProjectileDamage; }
};

#endif //PROJECTILE_H
