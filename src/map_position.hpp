#ifndef MAP_POSITION_H
#define MAP_POSITION_H

// Glm vectors don't want to cooperate, so I may be forced to work with this handcrafted atrocity below. I'm sorry that you have to look at this
struct MapPosition {
    int x, y;

    bool operator<(const MapPosition& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

#endif  // MAP_POSITION_H
