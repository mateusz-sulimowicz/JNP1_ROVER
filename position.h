#ifndef ROVER_POSITION_H
#define ROVER_POSITION_H

using coordinate_t = long long;

enum class Direction {
    NORTH, EAST, SOUTH, WEST
};

std::ostream &operator<<(std::ostream &os, const Direction &d) {
    switch (d) {
        case Direction::NORTH:
            os << "NORTH";
            return os;
        case Direction::EAST:
            os << "EAST";
            return os;
        case Direction::SOUTH:
            os <<  "SOUTH";
            return os;
        case Direction::WEST:
            os <<  "WEST";
            return os;
    }
}

struct Location {
    Location(coordinate_t x, coordinate_t y) : x(x), y(y) {}

    const coordinate_t x;
    const coordinate_t y;
};

struct Position {
public:
    Position(Location l, Direction d)
            : l(l), d(d) {}

    [[nodiscard]] Position forward() const {
        switch (d) {
            case Direction::NORTH:
                return {{l.x, l.y + 1}, d};
            case Direction::EAST:
                return {{l.x + 1, l.y}, d};
            case Direction::SOUTH:
                return {{l.x, l.y - 1}, d};
            case Direction::WEST:
                return {{l.x - 1, l.y}, d};
        }
    }

    [[nodiscard]] Position right() const {
        switch (d) {
            case Direction::NORTH:
                return {{l.x, l.y}, Direction::EAST};
            case Direction::EAST:
                return {{l.x, l.y}, Direction::SOUTH};
            case Direction::SOUTH:
                return {{l.x, l.y}, Direction::WEST};
            case Direction::WEST:
                return {{l.x, l.y}, Direction::NORTH};
        }
    }

    [[nodiscard]] Position left() const {
        switch (d) {
            case Direction::NORTH:
                return {{l.x, l.y}, Direction::WEST};
            case Direction::EAST:
                return {{l.x, l.y}, Direction::NORTH};
            case Direction::SOUTH:
                return {{l.x, l.y}, Direction::EAST};
            case Direction::WEST:
                return {{l.x, l.y}, Direction::SOUTH};
        }
    }

    [[nodiscard]] Position back() const {
        switch (d) {
            case Direction::NORTH:
                return {{l.x, l.y - 1}, d};
            case Direction::EAST:
                return {{l.x - 1, l.y}, d};
            case Direction::SOUTH:
                return {{l.x, l.y + 1}, d};
            case Direction::WEST:
                return {{l.x + 1, l.y}, d};
        }
    }

    const Location l;
    const Direction d;

    friend std::ostream &operator<<(std::ostream &os, const Position &p);
};

std::ostream &operator<<(std::ostream &os, const Position &p) {
    os << "("
       << p.l.x
       << ", "
       << p.l.y
       << " "
       << p.d
       << ")";
    return os;
}


#endif //ROVER_POSITION_H
