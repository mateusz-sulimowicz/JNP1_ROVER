#ifndef ROVER_COMMAND_H
#define ROVER_COMMAND_H

#include <iostream>
#include <utility>
#include <memory>
#include <vector>
#include "Position.h"
#include "Instruction.h"
#include "Sensor.h"

class Command {
public:
    Command(std::initializer_list<std::unique_ptr<Instruction>> i)
            : instr(i) {}

    [[nodiscard]] auto instructions_begin() const {
        return instr.begin();
    }

    [[nodiscard]] auto instructions_end() const {
        return instr.end();
    }

private:
    std::vector<std::unique_ptr<Instruction>> instr;

    friend Command compose(std::initializer_list<Command> &commands);
};

Command compose(std::initializer_list<Command> &commands) {
    Command res{};
    for (auto &c: commands) {
        res.instr.insert(res.instr.end(),
                         c.instr.begin(),
                         c.instr.end());
    }
    return res;
}

Command move_forward() {
    return Command({std::make_unique<MoveForward>()});
}

Command move_back() {
    return Command({std::make_unique<MoveBack>()});
}

Command rotate_left() {
    return Command({std::make_unique<RotateLeft>()});
}

Command rotate_right() {
    return Command({std::make_unique<RotateRight>()});
}


#endif //ROVER_COMMAND_H
