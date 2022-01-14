#ifndef ROVER_COMMAND_H
#define ROVER_COMMAND_H

#include <iostream>
#include <utility>
#include <memory>
#include <vector>
#include "position.h"
#include "instruction.h"
#include "sensor.h"

class Command {
public:
    Command(std::initializer_list<std::shared_ptr<Instruction>> instructions)
        : instr(instructions) {
    }

    [[nodiscard]] auto begin() const {
        return instr.begin();
    }

    [[nodiscard]] auto end() const {
        return instr.end();
    }

private:
    std::vector<std::shared_ptr<Instruction>> instr;

    friend Command compose(std::initializer_list<Command> commands);
};

Command compose(std::initializer_list<Command> commands) {
    Command res{};
    for (auto &command: commands) {
       res.instr.insert(res.instr.end(),
                        command.instr.begin(),
                        command.instr.end());
    }
    return res;
}

Command move_forward() {
    return Command({std::make_shared<MoveForward>()});
}

Command move_backward() {
    return Command({std::make_shared<MoveBack>()});
}

Command rotate_left() {
    return Command({std::make_shared<RotateLeft>()});
}

Command rotate_right() {
    return Command({std::make_shared<RotateRight>()});
}


#endif //ROVER_COMMAND_H
