#include "enemy_manager.hpp"

#include "utils/rng.hpp"

std::vector<glm::vec2> EnemyManager::Simulate(float deltaTime, const std::map<MapPosition, unsigned int> &mapData , Player* player)
{
    std::vector<glm::vec2> _loot_positions;
    for (const Enemy& _enemy : m_Enemies)
    {
        if (!_enemy.IsAlive() && RNG::GetRNG().GetNextInt(0, 10) <= 4) {
            _loot_positions.push_back(_enemy.GetTransform().GetPosition());
            // Loot _loot(m_RenderMeshes["food"]);
            // _loot.GetTransform().SetPosition(_enemy.GetTransform().GetPosition());
            // m_Loot.push_back(_loot);
        }
    }
    std::erase_if(m_Enemies, [](const Enemy& _enemy)
    {
        return !_enemy.IsAlive();
    });
    for (Enemy& _enemy : m_Enemies)
    {
        _enemy.Simulate(deltaTime, mapData, *player);
        if (_enemy.Overlaps(*player))
        {
            player->DamagePlayer(deltaTime, _enemy.GetContactDamagePerSecond());
        }
    }
    return _loot_positions;
}

void EnemyManager::Draw(const Renderer *renderer, const Player *player) const
{
    for (const Enemy& _enemy : m_Enemies)
    {
        _enemy.Display(*renderer, player->GetViewMatrix());
    }
}

void EnemyManager::RegisterEnemyPrefabricate(const EnemyPrefabricate& enemy_prefabricate)
{
    m_Prefabricates.push_back(enemy_prefabricate);
}

bool EnemyManager::IsEnemyInPlayerRange(Player *player) const
{
    const float _rangeSq = std::pow(player->GetRange(), 2);
    for (const Enemy& _enemy : m_Enemies)
    {
        if (!_enemy.IsAlive()) continue;
        const glm::vec2 _delta = _enemy.GetTransform().GetPosition() - player->GetTransform().GetPosition();
        if (glm::dot(_delta, _delta) <= _rangeSq)
        {
            return true;
        }
    }
    return false;
}

void EnemyManager::PopulateMapWithEnemies(Map *map, Player* player, RenderMesh* render_mesh)
{
    ClearEnemies();
    std::vector<glm::vec2> _enemy_positions = map->PopulateMapWithEnemies(0.2);
    for (glm::vec2 _position : _enemy_positions)
    {
        int _enemy_index = RNG::GetRNG().GetNextInt(0, m_Prefabricates.size() - 1);
        Enemy _enemy(m_Prefabricates.at(_enemy_index));
        // Enemy _enemy(m_Prefabricates.at(_enemy_index).GetSpriteColumn(), m_Prefabricates.at(_enemy_index).GetSpriteRow());
        // _enemy.SetMesh(m_Prefabricates.at(_enemy_index).GetRenderMesh());
        _enemy.GetTransform().SetPosition(_position);
        m_Enemies.push_back(_enemy);
    }
    std::erase_if(m_Enemies, [&](const Enemy& _enemy)
    {
        const float _difference = glm::distance(_enemy.GetTransform().GetPosition(), player->GetTransform().GetPosition());
        const double _erasureRange = _enemy.GetDetectionRange() * 1.5;
        return _difference < _erasureRange;
    });
}
