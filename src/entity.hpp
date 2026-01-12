#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <glm/glm.hpp>
#include "game_element.hpp"

class Entity : virtual public GameElement
{
protected:
    glm::vec2 m_Velocity;
    glm::vec2 m_Acceleration;
    std::vector<glm::vec2> m_Forces;  // Because I'm not implementing mass, this should be rather interpreted as an intention of where I want the Entity to be moved to. Or we can just pretend that everything has the mass of 1 unit. This approach may change in the future.

    // bool m_kolizjaKolo;
    // bool m_kolizjaKwadrat;
    // double m_kolizjaKoloŚrenica;
    // double m_kolizjaKwadratBok;
public:
    Entity();
    ~Entity() noexcept;

    // void kolizja(Entity& innyEntity);
    void Simulate(float deltaTime) override;
    void AddForce(glm::vec2 force);

    inline glm::vec2 GetVelocity() const { return m_Velocity; }
};

#endif //ENTITY_H
