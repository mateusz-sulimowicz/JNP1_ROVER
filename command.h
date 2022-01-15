#ifndef ROVER_COMMAND_H
#define ROVER_COMMAND_H

#include <iostream>
#include <utility>
#include <memory>
#include <vector>
#include "instruction.h"

using Command = std::vector<std::shared_ptr<Instruction>>;

Command compose(std::initializer_list<Command> commands) {
    Command res;
    for (auto &command: commands) {
        for (const auto &i : command) {
            res.push_back(i->clone());
        }
    }
    return res;
}

Command move_forward() {
    Command c;
    c.push_back(std::make_unique<MoveForward>());
    return c;
}

Command move_backward() {
    Command c;
    c.push_back(std::make_unique<MoveBack>());
    return c;
}

Command rotate_left() {
    Command c;
    c.push_back(std::make_unique<RotateLeft>());
    return c;
}

Command rotate_right() {
    Command c;
    c.push_back(std::make_unique<RotateRight>());
    return c;
}

#endif //ROVER_COMMAND_H
