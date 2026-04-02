#include "enemy_manager.hpp"

#include <algorithm>
#include <ranges>
#include "utils/rng.hpp"

std::vector<glm::vec2> EnemyManager::Simulate(float deltaTime, const std::map<MapPosition, unsigned int> &mapData , Player* player)
{
    auto _loot_view = m_Enemies | std::ranges::views::filter([](const Enemy& enemy){return !enemy.IsAlive();})
        | std::ranges::views::filter([](const Enemy& enemy){return RNG::GetRNG().GetNextInt(0, 10) <= 4;})
        | std::ranges::views::transform([](const Enemy& enemy){return enemy.GetTransform().GetPosition();});
    std::vector<glm::vec2> _loot_positions;
    std::ranges::copy(_loot_view, std::back_inserter(_loot_positions));
    std::erase_if(m_Enemies, [](const Enemy& _enemy) {
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
    auto _display_all = [&](const Enemy& enemy) {
        enemy.Display(*renderer, player->GetViewMatrix());
    };
    std::ranges::for_each(m_Enemies, _display_all);
}

void EnemyManager::RegisterEnemyPrefabricate(const EnemyPrefabricate& enemy_prefabricate)
{
    m_Prefabricates.push_back(enemy_prefabricate);
}

bool EnemyManager::IsEnemyInPlayerRange(Player *player) const
{
    const float _rangeSq = std::pow(player->GetRange(), 2);
    auto _enemy_in_range = [&](const Enemy& enemy) {
        const glm::vec2 _delta = enemy.GetTransform().GetPosition() - player->GetTransform().GetPosition();
        return glm::dot(_delta, _delta) <= _rangeSq;
    };
    auto _enemies_in_range = m_Enemies | std::ranges::views::filter(&Enemy::IsAlive);
    return std::ranges::any_of(_enemies_in_range ,_enemy_in_range);
}

void EnemyManager::PopulateMapWithEnemies(Map *map, Player* player, RenderMesh* render_mesh)
{
    ClearEnemies();
    std::vector<glm::vec2> _enemy_positions = map->PopulateMapWithEnemies(0.2);
    auto _create_enemy_at_position = [&](glm::vec2 position) {
        const int _enemy_index = RNG::GetRNG().GetNextInt(0, m_Prefabricates.size() - 1);
        Enemy _enemy(m_Prefabricates.at(_enemy_index));
        _enemy.GetTransform().SetPosition(position);
        m_Enemies.push_back(_enemy);
    };
    std::ranges::for_each(_enemy_positions, _create_enemy_at_position);
    std::erase_if(m_Enemies, [&](const Enemy& _enemy)
    {
        const float _difference = glm::distance(_enemy.GetTransform().GetPosition(), player->GetTransform().GetPosition());
        const double _erasureRange = _enemy.GetDetectionRange() * 1.5;
        return _difference < _erasureRange;
    });
}
