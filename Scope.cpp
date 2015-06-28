#include "Scope.hpp"
#include "Instruction.hpp"
#include "Declaration.hpp"

const VarDecl* Scope::findVar(const std::string& name) const {
    for (const VarDecl* var : _vars) {
        if (var->getName() == name)
            return var;
    }

    if (_parent)
        return _parent->findVar(name);

    return nullptr;
}

void Scope::addVariable(const VarDecl* vd) {
    _vars.emplace_back(vd);
    this->addInstruction(vd);
}

void Scope::addInstruction(const Instruction* instr) {
    if (!_instructions)
        _instructions.reset(new Array<const Instruction>());
    _instructions->add(instr);
}