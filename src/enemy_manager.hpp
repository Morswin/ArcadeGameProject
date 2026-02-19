#ifndef ENEMY_MANAGER_HPP
#define ENEMY_MANAGER_HPP

#include <vector>
#include <glm/glm.hpp>
#include "renderer/render_mesh.hpp"
#include "renderer/renderer.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "map.hpp"
#include "enemy_prefabricate.hpp"

class EnemyManager
{
private:
    std::vector<Enemy> m_Enemies{};
    std::vector<EnemyPrefabricate> m_Prefabricates{};
public:
    EnemyManager() = default;
    ~EnemyManager() noexcept = default;

    std::vector<glm::vec2> Simulate(float deltaTime, const std::map<MapPosition, unsigned int>& mapData, Player* player);
    void Draw(const Renderer* renderer, const Player* player) const;

    void RegisterEnemyPrefabricate(const EnemyPrefabricate& enemy_prefabricate);
    void PopulateMapWithEnemies(Map* map, Player* player, RenderMesh* render_mesh);
    bool IsEnemyInPlayerRange(Player* player) const;

    inline std::vector<Enemy>& GetEnemies() { return m_Enemies; }
    inline bool IsEmpty() const { return m_Enemies.empty(); }
private:
    inline void ClearEnemies() { m_Enemies.clear(); }
};

#endif //ENEMY_MANAGER_HPP