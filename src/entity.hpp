#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "game_element.hpp"
#include "collision.hpp"
#include "map_position.hpp"

class Entity : virtual public GameElement
{
protected:
    glm::vec2 m_Velocity;
    glm::vec2 m_Acceleration;
    std::vector<glm::vec2> m_Forces;  // Because I'm not implementing mass, this should be rather interpreted as an intention of where I want the Entity to be moved to. Or we can just pretend that everything has the mass of 1 unit. This approach may change in the future.
    Collision m_Collision;
public:
    Entity(int spriteColumn, int spriteRow);
    ~Entity() noexcept;

    void Simulate(float deltaTime, const std::map<MapPosition, unsigned int>& mapData);
    void AddForce(glm::vec2 force);
    bool CollidesWithMap(const std::map<MapPosition, unsigned int>& mapData) const;
    bool Overlaps(const Entity& other) const;

    inline glm::vec2 GetVelocity() const { return m_Velocity; }
};

#endif //ENTITY_H
