#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "entity.hpp"

class Player : public Entity
{
private:
    const float m_MovementSpeed = 2.1f;
    glm::vec2 m_View;  // May be understood as the camera position. This will be utilized later.
    float m_SlowingFactor = 0.02f;  // For slowing player character down, when no input has been detected.
    bool m_IsMoving = false;  // Flag to be enabled with each run of the SetMovementInputForce method, determining whether to slow down or not in the Simulate method.
    // poziomPostaci  // Nie wiem czy tego inaczej nie rozwiążę
public:
    Player(int spriteColumn, int spriteRow);
    ~Player() noexcept;

    void Simulate(float deltaTime, const std::map<MapPosition, unsigned int>& mapData);
    void SetMovementInputForce(glm::vec2 input);
    glm::mat4 GetViewMatrix() const;

    inline glm::vec2 GetView() const { return m_View; }
    // void zbierzZdobycz();  // Prawdopodobnie wzorzec Obserwator z Zdobyczami, żeby te mogły trafnie reagować na gracza
};

#endif //PLAYER_H
