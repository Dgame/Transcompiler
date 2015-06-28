#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <memory>
#include <vector>

#include "Array.hpp"
#include "Visitor.hpp"

class Instruction;
class VarDecl;

class Scope {
private:
    std::unique_ptr<Array<const Instruction>> _instructions;
    const Scope* _parent = nullptr;
    std::vector<const VarDecl*> _vars;

public:
    explicit Scope(const Scope* parent = nullptr) : _parent(parent) { }

    const VarDecl* findVar(const std::string&) const;
    void addVariable(const VarDecl*);
    void addInstruction(const Instruction*);

    const Array<const Instruction>* getInstructions() const {
        return _instructions.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

#endif