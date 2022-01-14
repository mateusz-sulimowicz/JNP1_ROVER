#ifndef ROVER_COMMAND_H
#define ROVER_COMMAND_H

#include <iostream>
#include <utility>
#include <memory>
#include <vector>
#include "instruction.h"

using Command = std::vector<std::shared_ptr<Instruction>>;

Command compose(std::initializer_list<Command> commands) {
    Command res{};
    for (auto &command: commands) {
       res.insert(res.end(),
                        std::make_move_iterator(command.begin()),
                        std::make_move_iterator(command.end()));
    }
    return res;
}

Command move_forward() {
    return {std::make_unique<MoveForward>()};
}

Command move_backward() {
    return {std::make_unique<MoveBack>()};
}

Command rotate_left() {
    return {std::make_unique<RotateLeft>()};
}

Command rotate_right() {
    return {std::make_unique<RotateRight>()};
}

#endif //ROVER_COMMAND_H
