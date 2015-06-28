#include "Expression.hpp"
#include "Declaration.hpp"

VarExpr::VarExpr(const VarDecl* vd) : _var(vd) { }

void ArrayExpr::addExpr(const Expr* exp) {
    if (!_expr)
        _expr.reset(new Array<const Expr>());
    _expr->add(exp);
}

const std::unordered_map<std::string, std::string> PropertyExpr::Properties = {
    {"length", "size"}
};

const std::string& PropertyExpr::getProperty() const {
    auto it = Properties.find(_property);
    if (it != Properties.end())
        return it->second;
    return _property;
}
