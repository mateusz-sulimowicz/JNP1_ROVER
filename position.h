#ifndef ROVER_POSITION_H
#define ROVER_POSITION_H

using coordinate_t = long long;

enum class Direction {
    NORTH, EAST, SOUTH, WEST
};

// Returns direction on the right
Direction operator++(const Direction &d) {
    switch (d) {
        case Direction::NORTH:
            return Direction::EAST;
        case Direction::EAST:
            return Direction::SOUTH;
        case Direction::SOUTH:
            return Direction::WEST;
        case Direction::WEST:
            return Direction::NORTH;
        default:
            throw std::exception{};
    }
}

// Returns direction on the left
Direction operator--(const Direction &d) {
    switch (d) {
        case Direction::NORTH:
            return Direction::WEST;
        case Direction::WEST:
            return Direction::SOUTH;
        case Direction::SOUTH:
            return Direction::EAST;
        case Direction::EAST:
            return Direction::NORTH;
        default:
            throw std::exception{};
    }
}

std::ostream &operator<<(std::ostream &os, const Direction &d) {
    switch (d) {
        case Direction::NORTH:
            os << "NORTH";
            return os;
        case Direction::EAST:
            os << "EAST";
            return os;
        case Direction::SOUTH:
            os << "SOUTH";
            return os;
        case Direction::WEST:
            os << "WEST";
            return os;
        default:
            return os;
    }
}

class Location {
public:
    Location(coordinate_t x, coordinate_t y) : x(x), y(y) {}

private:
    const coordinate_t x;
    const coordinate_t y;

    friend Location operator+(const Location &a, const Location &b) {
        return {a.x + b.x, a.y + b.y};
    }

    friend Location operator-(const Location &a, const Location &b) {
        return {a.x - b.x, a.y - b.y};
    }

    friend std::ostream &operator<<(std::ostream &os, const Location &l) {
        os << "("
           << l.x
           << ", "
           << l.y
           << ")";
        return os;
    }

    friend class Position;
};

class Position {
public:
    Position(Location l, Direction d)
            : l(l), d(d) {}

    [[nodiscard]] Position forward() const {
        return {l + delta(), d};
    }

    [[nodiscard]] Position right() const {
        return {l, ++d};
    }

    [[nodiscard]] Position left() const {
        return {l, --d};
    }

    [[nodiscard]] Position back() const {
        return {l - delta(), d};
    }

    [[nodiscard]] coordinate_t get_x() const {
    	return l.x;
    }

    [[nodiscard]] coordinate_t get_y() const {
    	return l.y;
    }

private:
    const Location l;
    const Direction d;

    [[nodiscard]] Location delta() const {
        switch (d) {
            case Direction::NORTH:
                return {0, 1};
            case Direction::EAST:
                return {1, 0};
            case Direction::SOUTH:
                return {0, -1};
            case Direction::WEST:
                return {-1, 0};
            default:
                throw std::exception{};
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Position &p) {
        os << p.l
           << " "
           << p.d;
        return os;
    }
};


#endif //ROVER_POSITION_H
