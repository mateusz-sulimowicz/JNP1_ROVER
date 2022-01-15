#ifndef ROVER_ROVER_H
#define ROVER_ROVER_H

#include <unordered_map>
#include <utility>
#include <cassert>
#include "command.h"
#include "sensor.h"

class RoverNotLanded : public std::logic_error {
public:
    RoverNotLanded() : logic_error("Rover has not landed yet.") {}
};

class Rover {
public:
    using Program = std::unordered_map<char, Command>;
    using SensorModule = std::vector<std::unique_ptr<Sensor>>;

    void land(Location l, Direction d) {
        p = std::make_unique<Position>(l, d);
    }

    void execute(const std::string &commands) {
        if (!has_landed()) {
            throw RoverNotLanded{};
        }

        bool success = true;
        for (char c: commands) {
            success = execute(c);
            if (!success) {
                break;
            }
        }
        is_stopped = !success;
    }

private:
    const Program program;
    const SensorModule sensors;
    bool is_stopped = false;
    std::unique_ptr<Position> p = nullptr;

    // Rover is instantiable only through RoverBuilder.
    Rover(Program program, SensorModule sensors) :
            program(std::move(program)),
            sensors(std::move(sensors)) {}

    bool execute(char command) {
        assert(has_landed());
        if (!command_exists(command)) {
            return false;
        }

        for (const auto &instr: program.at(command)) {
            Position next_pos = instr->execute(*p);
            if (!is_safe(next_pos.get_x(), next_pos.get_y())) {
                return false;
            }
            p = std::make_unique<Position>(next_pos);
        }
        return true;
    }

    bool is_safe(coordinate_t x, coordinate_t y) const {
        for (const auto &s: sensors) {
            if (!s->is_safe(x, y)) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] bool has_landed() const {
        return p != nullptr;
    }

    bool command_exists(char name) {
        return program.find(name) != program.end();
    }

    friend std::ostream &operator<<(std::ostream &os, const Rover &r) {
        if (!r.has_landed()) {
            os << "unknown";
        } else {
            os << *(r.p);
            if (r.is_stopped) {
                os << " stopped";
            }
        }
        return os;
    }

    friend class RoverBuilder;
};

class RoverBuilder {
public:
    RoverBuilder &program_command(char name, Command command) {
        program.insert({name, std::move(command)});
        return *this;
    }

    RoverBuilder &add_sensor(std::unique_ptr<Sensor> sensor) {
        sensors.push_back(std::move(sensor));
        return *this;
    }

    Rover build() {
        return {std::move(program),
                std::move(sensors)};
    }

private:
    typename Rover::Program program{};
    typename Rover::SensorModule sensors{};
};

#endif //ROVER_ROVER_H
