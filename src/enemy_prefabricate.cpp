#include "enemy_prefabricate.hpp"

EnemyPrefabricate::EnemyPrefabricate(
    double detection_range, float wander_speed, float chase_speed, double contact_damage_per_second,
    int enemy_health, RenderMesh *render_mesh, int sprite_column, int sprite_row
    )
    : m_DetectionRange(detection_range), m_WanderSpeed(wander_speed), m_ChaseSpeed(chase_speed),
    m_ContactDamagePerSecond(contact_damage_per_second), m_EnemyHealth(enemy_health),
    m_RenderMesh(render_mesh), m_SpriteColumn(sprite_column), m_SpriteRow(sprite_row)
{
}
