#include "CVisitor.hpp"

#include "Type.hpp"
#include "Declaration.hpp"
#include "Statement.hpp"
#include "Scope.hpp"
#include "FormatVisitor.hpp"

void CVisitor::visit(const AddExpr* me) {
    me->getLeftExpr()->accept(this);
    _out << " + ";
    me->getRightExpr()->accept(this);
}

void CVisitor::visit(const SubExpr* me) {
    me->getLeftExpr()->accept(this);
    _out << " - ";
    me->getRightExpr()->accept(this);
}

void CVisitor::visit(const MulExpr* me) {
    me->getLeftExpr()->accept(this);
    _out << " * ";
    me->getRightExpr()->accept(this);
}

void CVisitor::visit(const DivExpr* me) {
    me->getLeftExpr()->accept(this);
    _out << " / ";
    me->getRightExpr()->accept(this);
}

void CVisitor::visit(const ModuloExpr* me) {
    me->getLeftExpr()->accept(this);
    _out << " % ";
    me->getRightExpr()->accept(this);
}

void CVisitor::visit(const BitAndExpr* me) {
    me->getLeftExpr()->accept(this);
    _out << " & ";
    me->getRightExpr()->accept(this);
}

void CVisitor::visit(const BitOrExpr* me) {
    me->getLeftExpr()->accept(this);
    _out << " | ";
    me->getRightExpr()->accept(this);
}

void CVisitor::visit(const CompareExpr* ce) {
    ce->getLeftExpr()->accept(this);
    this->CVisitor::visit(ce->getCompare());
    ce->getRightExpr()->accept(this);
}

void CVisitor::visit(const AssignExpr* ae) {
    _out << " = ",
    ae->getExpr()->accept(this);
}

void CVisitor::visit(const Compare cmp) {
    switch (cmp) {
        case Compare::Equal:
            _out << " == ";
        break;
        case Compare::Lower:
            _out << " < ";
        break;
        case Compare::Greater:
            _out << " > ";
        break;
        case Compare::GreaterOrEqual:
            _out << " >= ";
        break;
        case Compare::LowerOrEqual:
            _out << " <= ";
        break;
    }
}

void CVisitor::visit(const CastExpr* ce) {
    const Cast cast = ce->getCast();

    if (cast == Cast::C) {
        _out << '(';
        this->visit(ce->getType());
        _out << ')';
        _out << " ";
        ce->getExpr()->accept(this);
    } else { // C++
        switch (cast) {
            case Cast::Static:
                _out << "static_cast";
            break;
            case Cast::Dynamic:
                _out << "dynamic_cast";
            break;
            case Cast::Const:
                _out << "const_cast";
            break;
            case Cast::ReInterpret:
                _out << "reinterpret_cast";
            break;
            default: assert(0);
        }

        _out << '<';
        this->visit(ce->getType());
        _out << '>';
        _out << '(';
        ce->getExpr()->accept(this);
        _out << ')';
    }
}

void CVisitor::visit(const ParenExpr* pe) {
    _out << '(';
    pe->getExpr()->accept(this);
    _out << ')';
}

void CVisitor::visit(const IndexExpr* ie) {
    _out << '[';
    ie->getExpr()->accept(this);
    _out << ']';
}

void CVisitor::visit(const ArrayExpr* ae) {
    _out << '{';
    this->visit(ae->getExpr());
    _out << '}';
}

void CVisitor::visit(const VarExpr* ve) {
    _out << ve->getVar()->getName();
}

void CVisitor::visit(const PropertyExpr* pe) {
    pe->getExpr()->accept(this);
    _out << '.';
    _out << pe->getProperty();
    _out << "()";
}

template <typename T>
void CVisitor::visit(const Array<T>* arr) {
    for (u16_t i = 0; i < arr->count(); i++) {
        (*arr)[i]->accept(this);
        if ((i + 1) < arr->count()) {
            _out << ", ";
        }
    }
}

void CVisitor::visit(const Type* tb) {
    this->visit(tb->getSTC());
    this->visit(tb->getBasicType());
}

void CVisitor::visit(const TypePointer* tp) {
    this->visit(tp->getSTC());
    tp->getNext()->accept(this);
    _out << '*';
}

void CVisitor::visit(const TypeDynamicArray* tda) {
    this->visit(tda->getSTC());
    _out << "std::vector<";
    tda->getNext()->accept(this);
    _out << '>';
}

void CVisitor::visit(const TypeStaticArray* tsa) {
    this->visit(tsa->getSTC());
    _out << "std::array<";
    tsa->getNext()->accept(this);
    _out << ", ";
    _out << tsa->getDim();
    _out << '>';
}

void CVisitor::visit(const StorageClass stc) {
    switch (stc) {
        case StorageClass::Const:
            _out << "const ";
        break;
        default: break;
    }
}

void CVisitor::visit(BasicType type) {
    switch (type) {
        case BasicType::Void:
            _out << "void";
        break;
        case BasicType::Char:
            _out << "char";
        break;
        case BasicType::Bool:
            _out << "bool";
        break;
        case BasicType::Int_8:
            _out << "i8_t";
        break;
        case BasicType::Int_16:
            _out << "i16_t";
        break;
        case BasicType::Int_32:
            _out << "i32_t";
        break;
        case BasicType::Int_64:
            _out << "i64_t";
        break;
        case BasicType::Uint_8:
            _out << "u8_t";
        break;
        case BasicType::Uint_16:
            _out << "u16_t";
        break;
        case BasicType::Uint_32:
            _out << "u32_t";
        break;
        case BasicType::Uint_64:
            _out << "u64_t";
        break;
        case BasicType::Size_t:
            _out << "size_t";
        break;
        case BasicType::Float_32:
            _out << "f32_t";
        break;
        case BasicType::Float_64:
            _out << "f64_t";
        break;
        case BasicType::Float_80:
            _out << "f80_t";
        break;
        default:
            assert(0);
    }
}

void CVisitor::visit(const VarDecl* vd) {
    if (!vd->getParent()) {
        vd->getType()->accept(this);
        _out << " ";
    }

    _out << vd->getName();

    const Expr* exp = vd->getExpr();
    if (exp)
        exp->accept(this);
}

void CVisitor::visit(const PrintDecl* pd) {
    _out << "printf";
    _out << '(';

    const Array<const Expr>* expr = pd->getExpr();

    const StringExpr* fmt = pd->getFormat();
    if (!fmt) {
        _out << '"';

        FormatVisitor fv(_out);
        for (u16_t i = 0; i < expr->count(); i++) {
            (*expr)[i]->accept(&fv);
        }

        _out << '"';
    } else {
        fmt->accept(this);
    }

    _out << ", ";

    this->visit(expr);

    _out << ')';
}

void CVisitor::visit(const Parameter* param) {
    param->getType()->accept(this);
    if (param->getName().size() != 0)
        _out << " ";
    _out << param->getName();
}

void CVisitor::visit(const FuncDecl* fd) {
    fd->getType()->accept(this);
    _out << " ";
    _out << fd->getName();
    _out << '(';

    this->visit(fd->getParameter());

    _out << ')';

    const Scope* sc = fd->getScope();
    if (sc)
        sc->accept(this);
    else
        _out << ';';
}

void CVisitor::visit(const IfStmt* stmt) {
    _out << "if (";
    stmt->getExpr()->accept(this);
    _out << ')';
    stmt->getScope()->accept(this);
}

void CVisitor::visit(const ImportStmt* stmt) {
    _out << std::endl;
    _out << "#include";
    _out << " ";
    stmt->getExpr()->accept(this);
    _out << std::endl;
}

void CVisitor::visit(const ForLoopStmt* stmt) {
    _out << "for (";
    stmt->getInitVar()->accept(this);
    _out << ';';
    _out << " ";
    stmt->getCondExpr()->accept(this);
    _out << ';';
    _out << " ";
    stmt->getLoopVar()->accept(this);
    _out << ')';
    stmt->getScope()->accept(this);
}

void CVisitor::visit(const ForEachLoopStmt* stmt) {
    _out << "for (";
    stmt->getVar()->accept(this);
    _out << " : ";
    stmt->getExpr()->accept(this);
    _out << ')';
    stmt->getScope()->accept(this);
}

void CVisitor::visit(const Scope* scope) {
    _out << std::endl << '{' << std::endl;

    const Array<const Instruction>* instr = scope->getInstructions();
    for (u32_t i = 0; instr && i < instr->count(); i++) {
        _out << "\t";
        (*instr)[i]->accept(this);
        _out << ';';
    }

    _out << std::endl << '}' << std::endl;
}
