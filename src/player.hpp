#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "entity.hpp"

class Player : public Entity
{
private:
    const float m_MovementSpeed{2.1f};
    glm::vec2 m_View;  // May be understood as the camera position. This will be utilized later.
    float m_SlowingFactor{0.02f};  // For slowing player character down, when no input has been detected.
    bool m_IsMoving{false};  // Flag to be enabled with each run of the SetMovementInputForce method, determining whether to slow down or not in the Simulate method.
    double m_InitialHealthPoints{100.0};  // A reference health point amount, used for example when levelling up, or restarting game
    double m_CurrentHealthPoints;  // Health points present in the instance
public:
    Player(int spriteColumn, int spriteRow);
    ~Player() noexcept;

    void Simulate(float deltaTime, const std::map<MapPosition, unsigned int>& mapData);
    void SetMovementInputForce(glm::vec2 input);
    glm::mat4 GetViewMatrix() const;

    inline glm::vec2 GetView() const { return m_View; }
    inline bool IsAlive() const { return m_CurrentHealthPoints > 0.0; }
    inline void DamagePlayer(float deltaTime, double damagePerSecond) { m_CurrentHealthPoints -= damagePerSecond * deltaTime; }
    inline void HealCompletely() { m_CurrentHealthPoints = m_InitialHealthPoints; }
};

#endif //PLAYER_H
