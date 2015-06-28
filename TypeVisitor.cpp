#include <limits>

#include "TypeVisitor.hpp"
#include "Type.hpp"
#include "Expression.hpp"
#include "Declaration.hpp"

void TypeVisitor::visit(const IntExpr* ie) {
    BasicType type;

    if (ie->getValue() >= 0) {
        if (std::numeric_limits<u8_t>::max() > ie->getValue()) {
            type = BasicType::Uint_8;
        } else if (std::numeric_limits<u16_t>::max() > ie->getValue()) {
            type = BasicType::Uint_16;
        } else {
            type  = BasicType::Uint_32;
        }
    } else {
        if (std::numeric_limits<i8_t>::max() > ie->getValue()) {
            type = BasicType::Int_8;
        } else if (std::numeric_limits<i16_t>::max() > ie->getValue()) {
            type = BasicType::Int_16;
        } else {
            type  = BasicType::Int_32;
        }
    }

    this->types.push_back(type);
}

void TypeVisitor::visit(const FloatExpr* fe) {
    BasicType type;

    if (std::numeric_limits<f32_t>::max() > fe->getValue()) {
        type = BasicType::Float_32;
    } else if (std::numeric_limits<f64_t>::max() > fe->getValue()) {
        type = BasicType::Float_64;
    } else {
        type = BasicType::Float_80;
    }

    this->types.push_back(type);
}

template <typename T>
void TypeVisitor::visit(const Array<T>* arr) {
    for (u16_t i = 0; i < arr->count(); i++) {
        (*arr)[i]->accept(this);
    }
}

void TypeVisitor::visit(const BoolExpr*) {
    this->types.push_back(BasicType::Bool);
}

void TypeVisitor::visit(const CharExpr*) {
    this->types.push_back(BasicType::Char);
}

void TypeVisitor::visit(const AddExpr* me) {
    me->getLeftExpr()->accept(this);
    me->getRightExpr()->accept(this);
}

void TypeVisitor::visit(const SubExpr* me) {
    me->getLeftExpr()->accept(this);
    me->getRightExpr()->accept(this);
}

void TypeVisitor::visit(const MulExpr* me) {
    me->getLeftExpr()->accept(this);
    me->getRightExpr()->accept(this);
}

void TypeVisitor::visit(const DivExpr* me) {
    me->getLeftExpr()->accept(this);
    me->getRightExpr()->accept(this);
}

void TypeVisitor::visit(const ModuloExpr* me) {
    me->getLeftExpr()->accept(this);
    me->getRightExpr()->accept(this);
}

void TypeVisitor::visit(const BitAndExpr* me) {
    me->getLeftExpr()->accept(this);
    me->getRightExpr()->accept(this);
}

void TypeVisitor::visit(const BitOrExpr* me) {
    me->getLeftExpr()->accept(this);
    me->getRightExpr()->accept(this);
}

void TypeVisitor::visit(const CompareExpr* me) {
    me->getLeftExpr()->accept(this);
    me->getRightExpr()->accept(this);
}

void TypeVisitor::visit(const AssignExpr* exp) {
    exp->getExpr()->accept(this);
}

void TypeVisitor::visit(const CastExpr* exp) {
    exp->getExpr()->accept(this);
}

void TypeVisitor::visit(const ParenExpr* exp) {
    exp->getExpr()->accept(this);
}

void TypeVisitor::visit(const IndexExpr* exp) {
    exp->getExpr()->accept(this);
}

void TypeVisitor::visit(const ArrayExpr* exp) {
    this->visit(exp->getExpr());
}

void TypeVisitor::visit(const VarExpr* ve) {
    ve->getVar()->accept(this);
}

void TypeVisitor::visit(const VarDecl* vd) {
    vd->getExpr()->accept(this);
}
