#ifndef VISITOR_HPP
#define VISITOR_HPP

class IntExpr;
class FloatExpr;
class BoolExpr;
class CharExpr;
class StringExpr;
class AddExpr;
class SubExpr;
class MulExpr;
class DivExpr;
class ModuloExpr;
class CompareExpr;
class BitAndExpr;
class BitOrExpr;
class AssignExpr;
class CastExpr;
class ParenExpr;
class IndexExpr;
class NullExpr;
class ArrayExpr;
class VarExpr;
class PropertyExpr;

class Type;
class TypePointer;
class TypeDynamicArray;
class TypeStaticArray;

class VarDecl;
class PrintDecl;
class Parameter;
class Return;
class FuncDecl;

class IfStmt;
class ImportStmt;
class ForLoopStmt;
class ForEachLoopStmt;

class Scope;

enum class Compare;
enum class BasicType;
enum class StorageClass;

class Visitor {
public:
    virtual void visit(const IntExpr*) { }
    virtual void visit(const FloatExpr*) { }
    virtual void visit(const BoolExpr*) { }
    virtual void visit(const CharExpr*) { }
    virtual void visit(const StringExpr*) { }
    virtual void visit(const AddExpr*) { }
    virtual void visit(const SubExpr*) { }
    virtual void visit(const MulExpr*) { }
    virtual void visit(const DivExpr*) { }
    virtual void visit(const ModuloExpr*) { }
    virtual void visit(const BitAndExpr*) { }
    virtual void visit(const BitOrExpr*) { }
    virtual void visit(const CompareExpr*) { }
    virtual void visit(const AssignExpr*) { }
    virtual void visit(const CastExpr*) { }
    virtual void visit(const ParenExpr*) { }
    virtual void visit(const IndexExpr*) { }
    virtual void visit(const NullExpr*) { }
    virtual void visit(const ArrayExpr*) { }
    virtual void visit(const VarExpr*) { }
    virtual void visit(const PropertyExpr*) { }

    virtual void visit(const Type*) { }
    virtual void visit(const TypePointer*) { }
    virtual void visit(const TypeDynamicArray*) { }
    virtual void visit(const TypeStaticArray*) { }

    virtual void visit(const StorageClass) { }
    virtual void visit(const Compare) { }
    virtual void visit(const BasicType) { }

    virtual void visit(const VarDecl*) { }
    virtual void visit(const PrintDecl*) { }
    virtual void visit(const Parameter*) { }
    virtual void visit(const Return*) { }
    virtual void visit(const FuncDecl*) { }

    virtual void visit(const IfStmt*) { }
    virtual void visit(const ImportStmt*) { }
    virtual void visit(const ForLoopStmt*) { }
    virtual void visit(const ForEachLoopStmt*) { }

    virtual void visit(const Scope*) { }
};

#endif
