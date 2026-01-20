#include "map.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>
#include "utils/rng.hpp"

// TODO - move the change of visibility range to display, and make it react to the change in zoom setting
Map::Map() : m_VisibleRange(glm::vec2(10.0f, 8.0f)) {
    GenerateNewMap();
}

Map::~Map() {
}

void Map::DisplayFloorAndWall(Player& player, Renderer& renderer) {
    int lowX, highX, lowY, highY;
    glm::vec2 playerPosition = player.GetTransform().GetPosition();
    lowX = static_cast<int>(std::floor(playerPosition.x - m_VisibleRange.x));
    lowY = static_cast<int>(std::floor(playerPosition.y - m_VisibleRange.y));
    highX = static_cast<int>(std::ceil(playerPosition.x + m_VisibleRange.x));
    highY = static_cast<int>(std::ceil(playerPosition.y + m_VisibleRange.y));
    for (int x = lowX; x <= highX; x++) {
        for (int y = lowY; y <= highY; y++) {
            MapPosition _position{x, y};
            auto _dictionaryKey = m_PresentMapData.find(_position);
            if (_dictionaryKey != m_PresentMapData.end()) {
                m_EnvironmentDictionary.at(_dictionaryKey->second).GetTransform().SetPosition(glm::vec2(1.0f * x, 1.0f * y));
                m_EnvironmentDictionary.at(_dictionaryKey->second).Display(renderer, player.GetViewMatrix());
            }
        }
    }
}

void Map::RegisterNewEnvironment(unsigned int id, Environment&& environment) {
    m_EnvironmentDictionary.emplace(id, std::move(environment));
}

std::vector<Enemy> Map::PopulateMapWithEnemies(double percentage, RenderMesh* enemyRenderMesh) {
    std::vector<MapPosition> _possiblePositions;
    for (const auto& [_position, value] : m_PresentMapData) {
        if (value == 0 || value == 1) _possiblePositions.push_back(_position);
    }
    std::shuffle(_possiblePositions.begin(), _possiblePositions.end(), RNG::GetRNG().GetRNGEngine());
    const size_t _enemyCount = std::min(static_cast<size_t>(std::ceil(_possiblePositions.size() * percentage)), _possiblePositions.size());
    std::vector<Enemy> _enemies;
    _enemies.reserve(_enemyCount);
    for (size_t i = 0; i < _enemyCount; i++) {
        Enemy _enemy(0, 0);
        _enemy.SetMesh(enemyRenderMesh);
        _enemy.GetTransform().SetPosition(glm::vec2(
            _possiblePositions[i].x,
            _possiblePositions[i].y
        ));
        _enemies.push_back(_enemy);
    }
    return _enemies;
}

struct UnionFind {
    std::vector<int> parent;
    std::vector<int> rank;

    UnionFind(int n) : parent(n), rank(n, 0) {
        std::iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return false;

        if (rank[rx] < rank[ry]) parent[rx] = ry;
        else if (rank[rx] > rank[ry]) parent[ry] = rx;
        else { parent[ry] = rx; rank[rx]++; }
        return true;
    }
};

Room* getRoomById(std::vector<Room>& rooms, int id) {
    for (Room& room : rooms) {
        if (room.GetId() == id) return &room;
    }
    return nullptr;
}

void Map::GenerateNewMap() {
    // Generate all rooms
    std::vector<Room> _rooms;
    _rooms.reserve(m_NumberOfRooms);
    for (size_t i = 0; i < m_NumberOfRooms; i++) {
        Room _room(
            static_cast<unsigned int>(RNG::GetRNG().GetNextInt(1, 6)),
            static_cast<unsigned int>(RNG::GetRNG().GetNextInt(1, 6)),
            RNG::GetRNG().GetNextInt(-10, 10),
            RNG::GetRNG().GetNextInt(-10, 10)
        );
        _rooms.push_back(_room);
    }
    // Spread rooms that overlap with each other
    bool anyRoomOverlap;
    int separationIterations = 0;
    constexpr int MAX_SEPARATION_ITERATIONS = 100;
    do {
        anyRoomOverlap = false;
        separationIterations++;
        for (Room& _room : _rooms) {
            int totalPushX = 0;
            int totalPushY = 0;
            int neighboursCount = 0;
            for (Room& _other_room : _rooms) {
                if (&_room != &_other_room) {
                    if (_room.DoRoomsOverlap(_other_room)) {
                        anyRoomOverlap = true;
                        int roomCenterX  = _room.GetX() + _room.GetWidth() / 2;
                        int roomCenterY  = _room.GetY() + _room.GetHeight() / 2;
                        int otherCenterX = _other_room.GetX() + _other_room.GetWidth() / 2;
                        int otherCenterY = _other_room.GetY() + _other_room.GetHeight() / 2;
                        int dx = roomCenterX - otherCenterX;
                        int dy = roomCenterY - otherCenterY;
                        int overlapX = (_room.GetWidth() / 2 + _other_room.GetWidth() / 2) - std::abs(dx);
                        int overlapY = (_room.GetHeight() / 2 + _other_room.GetHeight() / 2) - std::abs(dy);
                        int pushX = 0;
                        int pushY = 0;
                        if (overlapX < overlapY) {
                            pushX = (dx > 0 ? overlapX : -overlapX);
                        } else {
                            pushY = (dy > 0 ? overlapY : -overlapY);
                        }
                        totalPushX += pushX;
                        totalPushY += pushY;
                        neighboursCount++;
                    }
                }
            }
            if (neighboursCount > 0) {
                _room.Push(
                    totalPushX / neighboursCount,
                    totalPushY / neighboursCount
                );
            }
        }
    } while (anyRoomOverlap && separationIterations < MAX_SEPARATION_ITERATIONS);
    // Filtering out rooms that are too small
    double _sumWidth  = 0.0;
    double _sumHeight = 0.0;
    for (const Room& _room : _rooms) {
        _sumWidth  += _room.GetWidth();
        _sumHeight += _room.GetHeight();
    }
    double _meanWidth  = _sumWidth  / _rooms.size();
    double _meanHeight = _sumHeight / _rooms.size();
    constexpr double THRESHOLD_MULTIPLIER = 1.25;
    double _widthThreshold  = _meanWidth  * THRESHOLD_MULTIPLIER;
    double _heightThreshold = _meanHeight * THRESHOLD_MULTIPLIER;
    std::vector<Room> _filteredRoom;
    _filteredRoom.reserve(_rooms.size());
    for (const Room& _room : _rooms) {
        if (_room.GetWidth()  >= _widthThreshold && _room.GetHeight() >= _heightThreshold) {
            _filteredRoom.push_back(_room);
        }
    }
    _rooms = std::move(_filteredRoom);
    // TODO - Use Delaynay algorithm in one of the future updates.
    // Brute force alternative to Delaynay algorithm (everything x everything). I'm lacking time to implement use of the right method.
    struct Point {
        int x;
        int y;
        int roomId;
    };
    std::vector<Point> _points;
    for (const Room& _room : _rooms) {
        _points.push_back({
            static_cast<int>(_room.GetX() + _room.GetWidth()/2),
            static_cast<int>(_room.GetY() + _room.GetHeight()/2),
            _room.GetId()
        });
    }
    struct Edge {
        int from;
        int to;
        double distance;
    };
    std::vector<Edge> _edges;
    for (size_t i = 0; i < _points.size(); ++i) {
        for (size_t j = i + 1; j < _points.size(); ++j) {
            const Point& _a = _points[i];
            const Point& _b = _points[j];
            double _dx = double(_a.x - _b.x);
            double _dy = double(_a.y - _b.y);
            double _distance = std::sqrt(_dx*_dx + _dy*_dy);
            _edges.push_back({_a.roomId, _b.roomId, _distance});
        }
    }
    // Minimum spanning tree with Kurskal's algorithm
    std::sort(_edges.begin(), _edges.end(), [](const Edge& a, const Edge& b){
        return a.distance < b.distance;
    });
    int n = _points.size();
    UnionFind uf(n);
    std::unordered_map<int, int> roomIdToIndex;
    for (int i = 0; i < n; ++i) roomIdToIndex[_points[i].roomId] = i;
    std::vector<Edge> _mst;
    for (const Edge& e : _edges) {
        int u = roomIdToIndex[e.from];
        int v = roomIdToIndex[e.to];
        if (uf.unite(u, v)) {
            _mst.push_back(e);
        }
    }
    // Creating corridoors
    struct Corridor {
        int x1, y1;
        int x2, y2;
    };
    std::vector<Corridor> _corridors;
    for (const Edge& e : _mst) {
        Room* a = getRoomById(_rooms, e.from);
        Room* b = getRoomById(_rooms, e.to);
        if (!a || !b) continue;
        int ax = a->GetX() + a->GetWidth()/2;
        int ay = a->GetY() + a->GetHeight()/2;
        int bx = b->GetX() + b->GetWidth()/2;
        int by = b->GetY() + b->GetHeight()/2;
        _corridors.push_back({ax, ay, bx, ay});
        _corridors.push_back({bx, ay, bx, by});
    }
    for (const Corridor& c : _corridors) {
        if (c.y1 == c.y2) {
            int y = c.y1;
            int xStart = std::min(c.x1, c.x2);
            int xEnd   = std::max(c.x1, c.x2);
            for (int x = xStart; x <= xEnd; ++x) {
                MapPosition pos{x, y};
                m_PresentMapData[pos] = 1;
            }
        } else if (c.x1 == c.x2) {
            int x = c.x1;
            int yStart = std::min(c.y1, c.y2);
            int yEnd   = std::max(c.y1, c.y2);
            for (int y = yStart; y <= yEnd; ++y) {
                MapPosition pos{x, y};
                m_PresentMapData[pos] = 1;
            }
        }
    }
    // Apply room data to the map data
    for (Room& _room : _rooms) {
        for (auto& [_mapPos, value] : _room.GetRoomData()) {
            m_PresentMapData[_mapPos] = value;
        }
    }
    // Adding walls, without autotile
    std::map<MapPosition, unsigned int> _walls;
    const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    for (const auto& [pos, value] : m_PresentMapData) {
        if (value != 0 && value != 1) continue;
        for (int i = 0; i < 8; ++i) {
            MapPosition neighbor{pos.x + dx[i], pos.y + dy[i]};
            auto it = m_PresentMapData.find(neighbor);
            if (it == m_PresentMapData.end() || (it->second != 0 && it->second != 1)) {
                _walls[neighbor] = 10;
            }
        }
    }
    for (const auto& [pos, value] : _walls) {
        m_PresentMapData[pos] = value;
    }
    // Set new player starting position
    const Room& _room = _rooms[0];
    int centerX = _room.GetX() + _room.GetWidth() / 2;
    int centerY = _room.GetY() + _room.GetHeight() / 2;
    MapPosition centerTile{centerX, centerY};
    if (m_PresentMapData[centerTile] != 0 && m_PresentMapData[centerTile] != 1) {
        for (int y = _room.GetY(); y < _room.GetY() + _room.GetHeight(); ++y) {
            for (int x = _room.GetX(); x < _room.GetX() + _room.GetWidth(); ++x) {
                if (m_PresentMapData[{x, y}] == 0 || m_PresentMapData[{x, y}] == 1) {
                    centerTile = {x, y};
                    goto found;
                }
            }
        }
        found:;
    }
    glm::vec2 center = glm::vec2(float(centerTile.x), float(centerTile.y));
    m_RelocatePlayerLocation = center;
    m_RelocatePlayer = true;
}

