#ifndef ROVER_ROVER_H
#define ROVER_ROVER_H

#include <unordered_map>
#include <utility>
#include <cassert>
#include "command.h"

class RoverNotLanded : public std::logic_error {
public:
    RoverNotLanded() : logic_error("Rover has not landed yet.") {}
};

class Rover {

public:
    using Program = std::unordered_map<char, Command>;
    using SensorModule = std::vector<std::shared_ptr<Sensor>>;

    Rover(Program &&program, SensorModule &&sensors) :
            program(program),
            sensors(sensors) {}

    void execute(const std::string &commands) {
        if (!is_landed()) {
            throw RoverNotLanded{};
        }

        bool success;
        for (char c : commands) {
            success = execute(c);
            if (!success) {
                break;
            }
        }
        is_stopped = !success;
    }

    void land(Location l, Direction d) {
        p = std::make_shared<Position>(l, d);
    }

private:
    const Program program;
    const SensorModule sensors;
    bool is_stopped = false;
    std::shared_ptr<Position> p = nullptr;

    bool execute(char command) {
        assert(is_landed());
        if (!command_exists(command)) {
            return false;
        }

        for (const auto &instr : program.at(command)) {
            Position next_pos = instr->execute(*p);
            if (!is_location_safe(next_pos.l)) {
                return false;
            }
            p = std::make_shared<Position>(next_pos.l, next_pos.d);
        }
        return true;
    }

    bool is_location_safe(Location l) const {
        for (const auto &s : sensors) {
            if (!s->is_safe(l.get_x(), l.get_y())) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] bool is_landed() const {
        return p != nullptr;
    }

    bool command_exists(char name) {
        return program.find(name) != program.end();
    }

    friend std::ostream &operator<<(std::ostream &os, const Rover &r);

};

std::ostream &operator<<(std::ostream &os, const Rover &r) {
    if (!r.is_landed()) {
        os << "unknown";
    } else {
        os << *(r.p);
        if (r.is_stopped) {
            os << " stopped";
        }
    }
    return os;
}

class RoverBuilder {
public:
    RoverBuilder program_command(char name, Command &&command) {
        program.insert({name, command});
        return *this;
    }

    RoverBuilder add_sensor(std::shared_ptr<Sensor> &&sensor) {
        sensors.push_back(sensor);
        return *this;
    }

    Rover build() {
        return {std::move(program), std::move(sensors)};
    }

private:
    typename Rover::Program program{};
    typename Rover::SensorModule sensors{};
};

#endif //ROVER_ROVER_H
