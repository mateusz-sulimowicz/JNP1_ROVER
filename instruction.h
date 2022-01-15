#ifndef ROVER_INSTRUCTION_H
#define ROVER_INSTRUCTION_H

#include "position.h"

class Instruction {
public:
    virtual Position
    execute(const Position &p) = 0;

    virtual std::unique_ptr<Instruction> clone() = 0;

    virtual ~Instruction() = default;
};

class MoveForward : public Instruction {
public:
    Position execute(const Position &p) override {
        return p.forward();
    }

    std::unique_ptr<Instruction> clone() override {
        return std::make_unique<MoveForward>();
    }

    ~MoveForward() override = default;
};

class MoveBack : public Instruction {
public:
    Position execute(const Position &p) override {
        return p.back();
    }

    std::unique_ptr<Instruction> clone() override {
        return std::make_unique<MoveBack>();
    }

    ~MoveBack() override = default;
};

class RotateLeft : public Instruction {
public:
    Position execute(const Position &p) override {
        return p.left();
    }

    std::unique_ptr<Instruction> clone() override {
        return std::make_unique<RotateLeft>();
    }

    ~RotateLeft() override = default;
};

class RotateRight : public Instruction {
public:
    Position execute(const Position &p) override {
        return p.right();
    }

    std::unique_ptr<Instruction> clone() override {
        return std::make_unique<RotateRight>();
    }

    ~RotateRight() override = default;
};

#endif //ROVER_INSTRUCTION_H
