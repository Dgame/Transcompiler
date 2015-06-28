#ifndef SYMBOL_HPP
#define SYMBOL_HPP

class Visitor;

class Instruction {
public:
    virtual void accept(Visitor*) const = 0;
};

#endif