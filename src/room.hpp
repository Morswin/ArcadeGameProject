#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <cmath>
#include "map_position.hpp"

class Room {
private:
    unsigned int m_Width;
    unsigned int m_Height;
    unsigned int m_Radius;
    // Position will be calculated from the lower-left corner of the room
    int m_PositionX;
    int m_PositionY;
    int m_ID;

    static int nextRoomId;
public:
    Room(unsigned int width, unsigned int height, int x, int y);
    ~Room();

    std::map<MapPosition, unsigned int> GetRoomData();
    bool DoRoomsOverlap(Room& other_room);

    inline void Push(int x, int y) { m_PositionX += x; m_PositionY += y; }
    inline unsigned int GetWidth() const { return m_Width; }
    inline unsigned int GetHeight() const { return m_Height; }
    inline int GetX() const { return m_PositionX; }
    inline int GetY() const { return m_PositionY; }
    inline int GetId() const { return m_ID; }
};

#endif  // ROOM_H
