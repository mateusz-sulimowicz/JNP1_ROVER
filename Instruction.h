#ifndef ROVER_INSTRUCTION_H
#define ROVER_INSTRUCTION_H

#include "Position.h"

class Instruction {
public:
    virtual Position
    execute(const Position &p) = 0;

    virtual ~Instruction() = 0;
};

class MoveForward : public Instruction {
public:
    Position
    execute(const Position &p) override {
        return p.forward();
    }

    ~MoveForward() override = default;
};

class MoveBack : public Instruction {
public:
    Position
    execute(const Position &p) override {
        return p.back();
    }

    ~MoveBack() override = default;
};

class RotateLeft : public Instruction {
public:
    Position
    execute(const Position &p) override {
        return p.left();
    }

    ~RotateLeft() override = default;
};

class RotateRight : public Instruction {
public:
    Position
    execute(const Position &p) override {
        return p.right();
    }

    ~RotateRight() override = default;
};

#endif //ROVER_INSTRUCTION_H
