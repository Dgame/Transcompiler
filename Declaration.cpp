#include "Declaration.hpp"

const Type* VarDecl::getType() const {
    if (_parent)
        return _parent->getType();
    return _type.get();
}

void PrintDecl::addExpr(const Expr* exp) {
    if (!_exprs)
        _exprs.reset(new Array<const Expr>());
    _exprs->add(exp);
}

void FuncDecl::addParameter(const Parameter* param) {
    if (!_parameter)
        _parameter.reset(new Array<const Parameter>());
    _parameter->add(param);
}
