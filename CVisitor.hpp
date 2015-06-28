#ifndef C_VISITOR_HPP
#define C_VISITOR_HPP

#include <iostream>
#include <assert.h>

#include "Visitor.hpp"
#include "Expression.hpp"
#include "Declaration.hpp"

class CVisitor : public Visitor {
private:
    std::ostream& _out;

public:
    explicit CVisitor(std::ostream& stream) : _out(stream) { }

    void visit(const IntExpr* ie) override {
        _out << ie->getValue();
    }

    void visit(const FloatExpr* fe) override {
        _out << fe->getValue();
    }

    void visit(const BoolExpr* be) override {
        _out << (be->getValue() ? "true" : "false");
    }

    void visit(const CharExpr* ce) override {
        _out << "'" << ce->getValue() << "'";
    }

    void visit(const StringExpr* se) override {
        _out << '"' << se->getValue() << '"';
    }

    void visit(const AddExpr*) override;
    void visit(const SubExpr*) override;
    void visit(const MulExpr*) override;
    void visit(const DivExpr*) override;
    void visit(const ModuloExpr*) override;
    void visit(const BitAndExpr*) override;
    void visit(const BitOrExpr*) override;
    void visit(const CompareExpr*) override;
    void visit(const AssignExpr*) override;
    void visit(const Compare) override;
    void visit(const CastExpr*) override;
    void visit(const ParenExpr*) override;
    void visit(const IndexExpr*) override;

    virtual void visit(const Return* ret) override {
        _out << "return";
        _out << " ";
        ret->getExpr()->accept(this);
    }

    void visit(const NullExpr* ne) override {
        _out << "nullptr";
    }

    virtual void visit(const ArrayExpr*) override;
    virtual void visit(const VarExpr*) override;
    virtual void visit(const PropertyExpr*) override;

    template <typename T>
    void visit(const Array<T>*);

    void visit(const Type*) override;
    void visit(const TypePointer*) override;
    void visit(const TypeDynamicArray*) override;
    void visit(const TypeStaticArray*) override;
    void visit(const StorageClass) override;
    void visit(BasicType) override;

    void visit(const VarDecl*) override;
    void visit(const PrintDecl*) override;

    void visit(const Parameter*) override;
    void visit(const FuncDecl*) override;

    void visit(const IfStmt*) override;
    void visit(const ImportStmt*) override;
    void visit(const ForLoopStmt*) override;
    void visit(const ForEachLoopStmt*) override;

    void visit(const Scope*) override;

    std::ostream& getOutput() const {
        return _out;
    }
};


#endif
