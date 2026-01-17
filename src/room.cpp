#include "room.hpp"

// The static field initialization.
int Room::nextRoomId = 0;

Room::Room(unsigned int width, unsigned int height, int x, int y)
    : m_Width(width), m_Height(height), m_PositionX(x), m_PositionY(y), m_ID(Room::nextRoomId++)
{
    m_Radius = static_cast<unsigned int>(std::ceil(std::sqrt(1.0 * width * width + 1.0 * height * height)));
}

Room::~Room() {
}

std::map<MapPosition, unsigned int> Room::GetRoomData() {
    std::map<MapPosition, unsigned int> _room_data;
    for (int x = m_PositionX; x < m_PositionX + m_Width; x++) {
        for (int y = m_PositionY; y < m_PositionY + m_Height; y++) {
            MapPosition _tilePosition{x, y};
            _room_data[_tilePosition] = 0;
        }
    }
    return _room_data;
}

bool Room::DoRoomsOverlap(Room& other_room) {
    return !(
        m_PositionX + m_Width  < other_room.m_PositionX || // this right <= other left
        m_PositionX > other_room.m_PositionX + other_room.m_Width || // this left >= other right
        m_PositionY + m_Height < other_room.m_PositionY || // this top <= other bottom
        m_PositionY > other_room.m_PositionY + other_room.m_Height // this bottom >= other top
    );
}
