#ifndef ENEMY_PREFABRICATE_HPP
#define ENEMY_PREFABRICATE_HPP

#include "renderer/render_mesh.hpp"

class EnemyPrefabricate
{
private:
    double m_DetectionRange;
    float m_WanderSpeed;
    float m_ChaseSpeed;
    double m_ContactDamagePerSecond;
    int m_EnemyHealth;
    RenderMesh* m_RenderMesh;
    int m_SpriteColumn;
    int m_SpriteRow;

public:
    EnemyPrefabricate(
        double detection_range = 3.0, float wander_speed = 0.25f, float chase_speed = 0.6f,
        double contact_damage_per_second = 20.0, int enemy_health = 30, RenderMesh* render_mesh = nullptr,
        int sprite_column = 0, int sprite_row = 0
        );
    ~EnemyPrefabricate() = default;

    inline double GetDetectionRange() const { return m_DetectionRange; }
    inline float GetWanderSpeed() const { return m_WanderSpeed; }
    inline float GetChaseSpeed() const { return m_ChaseSpeed; }
    inline double GetContactDamagePerSecond() const { return m_ContactDamagePerSecond; }
    inline int GetEnemyHealth() const { return m_EnemyHealth; }
    inline RenderMesh* GetRenderMesh() const { return m_RenderMesh; }
    inline int GetSpriteColumn() const { return m_SpriteColumn; }
    inline int GetSpriteRow() const { return m_SpriteRow; }
};

#endif  //ENEMY_PREFABRICATE_HPP