#ifndef ROVER_ROVER_H
#define ROVER_ROVER_H

#include <unordered_map>
#include <utility>
#include "Command.h"

using Program = std::unordered_map<char, Command>;
using SensorModule = std::vector<std::unique_ptr<Sensor>>;

class Rover {
public:
    Rover(Program program,
          SensorModule sensors)
            : program(std::move(program)), sensors(std::move(sensors)) {}

    void execute(const std::string &commands) {
        if (!is_landed()) {
            // TODO: wyjatek
        }

        for (char c : commands) {
            if (program.find(c) == program.end()) {
                // TODO wyjatek
            }
            execute_command(program.at(c));
        }
    }

    void land(Location l, Direction d) {
        p = std::make_unique<Position>(l, d);
    }

private:
    const Program program;
    const SensorModule sensors;
    std::unique_ptr<Position> p = nullptr;

    void execute_command(const Command &c) {
        auto iter = c.instructions_begin();
        while (iter != c.instructions_end()) {
            ++iter;
            // TODO: update position
        }
    }

    [[nodiscard]] bool is_landed() const {
        return p != nullptr;
    }

    friend std::ostream& operator<< (std::ostream& os, const Rover& r);

};

std::ostream &operator<<(std::ostream& os, const Rover& r) {
    if (!r.is_landed()) {
        os << "unknown";
    } else {
        os << *(r.p);
    }
    return os;
}


class RoverBuilder {
public:
    RoverBuilder program_command(char name, const Command &command) {
        program[name] = command;
        return *this;
    }

    RoverBuilder add_sensor(std::unique_ptr<Sensor> &sensor) {
        sensors.push_back(std::move(sensor));
        return *this;
    }

    Rover build() const {
        return {program, sensors};
    }

private:
    Program program{};
    SensorModule sensors{};
};

#endif //ROVER_ROVER_H
