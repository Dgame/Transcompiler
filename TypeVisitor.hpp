#ifndef TYPE_VISITOR
#define TYPE_VISITOR

#include <assert.h>
#include <vector>
#include <algorithm>

#include "Visitor.hpp"
#include "Array.hpp"

enum class BasicType;

class TypeVisitor : public Visitor {
public:
    std::vector<BasicType> types;

    void visit(const IntExpr*) override;
    void visit(const FloatExpr*) override;
    void visit(const BoolExpr*) override;
    void visit(const CharExpr*) override;

    template <typename T>
    void visit(const Array<T>*);

    void visit(const AddExpr*) override;
    void visit(const SubExpr*) override;
    void visit(const MulExpr*) override;
    void visit(const DivExpr*) override;
    void visit(const ModuloExpr*) override;
    void visit(const BitAndExpr*) override;
    void visit(const BitOrExpr*) override;
    void visit(const CompareExpr*) override;
    void visit(const AssignExpr*) override;
    void visit(const CastExpr*) override;
    void visit(const ParenExpr*) override;
    void visit(const IndexExpr*) override;
    void visit(const ArrayExpr*) override;
    void visit(const VarExpr*) override;

    void visit(const PropertyExpr*) override {
        assert(0);
    }

    void visit(const VarDecl*) override;

    void visit(const StringExpr*) override {
        assert(0);
    }

    void visit(const NullExpr*) override {
        assert(0);
    }

    void visit(const Type*) override {
        assert(0);
    }

    void visit(const TypePointer*) override {
        assert(0);
    }

    void visit(const TypeDynamicArray*) override {
        assert(0);
    }

    void visit(const TypeStaticArray*) override {
        assert(0);
    }

    void visit(const StorageClass) override {
        assert(0);
    }

    void visit(const Compare) override {
        assert(0);
    }

    void visit(const BasicType) override {
        assert(0);
    }

    void visit(const PrintDecl*) override {
        assert(0);
    }

    void visit(const Parameter*) override {
        assert(0);
    }

    void visit(const Return*) override {
        assert(0);
    }

    void visit(const FuncDecl*) override {
        assert(0);
    }

    void visit(const IfStmt*) override {
        assert(0);
    }

    void visit(const ImportStmt*) override {
        assert(0);
    }

    void visit(const ForLoopStmt*) override {
        assert(0);
    }

    void visit(const ForEachLoopStmt*) override {
        assert(0);
    }

    void visit(const Scope*) override {
        assert(0);
    }

    BasicType getType() const {
        return *(std::max_element(this->types.begin(), this->types.end()));
    }
};

#endif
