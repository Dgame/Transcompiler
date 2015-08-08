#ifndef EXPR_HPP
#define EXPR_HPP

#include <unordered_map>

#include "Visitor.hpp"
#include "Array.hpp"

class Expr {
public:
    virtual void accept(Visitor*) const = 0;
};

class IntExpr : public Expr {
private:
    i32_t _value = 0;

public:
    explicit IntExpr(i32_t val) : _value(val) { }

    i32_t getValue() const {
        return _value;
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class FloatExpr : public Expr {
private:
    f32_t _value = 0;

public:
    explicit FloatExpr(f32_t val) : _value(val) { }

    f32_t getValue() const {
        return _value;
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class BoolExpr : public Expr {
private:
    bool _value = false;

public:
    explicit BoolExpr(bool val) : _value(val) { }

    bool getValue() const {
        return _value;
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class CharExpr : public Expr {
private:
    char _value;

public:
    explicit CharExpr(char val) : _value(val) { }

    char getValue() const {
        return _value;
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class StringExpr : public Expr {
private:
    const std::string _value;

public:
    explicit StringExpr(const std::string& val) : _value(val) { }

    const std::string& getValue() const {
        return _value;
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class UnaExpr : public Expr {
private:
    std::unique_ptr<const Expr> _exp;

public:
    explicit UnaExpr(const Expr* exp) : _exp(exp) { }

    const Expr* getExpr() const {
        return _exp.get();
    }
};

class AssignExpr : public UnaExpr {
public:
    explicit AssignExpr(const Expr* exp) : UnaExpr(exp) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

enum class Cast {
    Static,
    Dynamic,
    ReInterpret,
    Const,
    C
};

class CastExpr : public UnaExpr {
private:
    Cast _cast;
    std::shared_ptr<const Type> _type;

public:
    explicit CastExpr(std::shared_ptr<const Type> type, const Expr* exp, Cast cast = Cast::Static) : UnaExpr(exp), _type(type), _cast(cast) { }

    Cast getCast() const {
        return _cast;
    }

    const Type* getType() const {
        return _type.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class ParenExpr : public UnaExpr {
public:
    explicit ParenExpr(const Expr* exp) : UnaExpr(exp) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class IndexExpr : public UnaExpr {
public:
    explicit IndexExpr(const Expr* exp) : UnaExpr(exp) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class BinExpr : public Expr {
private:
    std::unique_ptr<const Expr> _left;
    std::unique_ptr<const Expr> _right;

public:
    explicit BinExpr(const Expr* lhs, const Expr* rhs) : _left(lhs), _right(rhs) { }

    const Expr* getLeftExpr() const {
        return _left.get();
    }

    const Expr* getRightExpr() const {
        return _right.get();
    }
};

class AddExpr : public BinExpr {
public:
    explicit AddExpr(const Expr* lhs, const Expr* rhs) : BinExpr(lhs, rhs) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class SubExpr : public BinExpr {
public:
    explicit SubExpr(const Expr* lhs, const Expr* rhs) : BinExpr(lhs, rhs) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class MulExpr : public BinExpr {
public:
    explicit MulExpr(const Expr* lhs, const Expr* rhs) : BinExpr(lhs, rhs) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class DivExpr : public BinExpr {
public:
    explicit DivExpr(const Expr* lhs, const Expr* rhs) : BinExpr(lhs, rhs) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class ModuloExpr : public BinExpr {
public:
    explicit ModuloExpr(const Expr* lhs, const Expr* rhs) : BinExpr(lhs, rhs) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class BitAndExpr : public BinExpr {
public:
    explicit BitAndExpr(const Expr* lhs, const Expr* rhs) : BinExpr(lhs, rhs) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class BitOrExpr : public BinExpr {
public:
    explicit BitOrExpr(const Expr* lhs, const Expr* rhs) : BinExpr(lhs, rhs) { }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

enum class Compare {
    Equal,
    Greater,
    Lower,
    LowerOrEqual,
    GreaterOrEqual
};

class CompareExpr : public BinExpr {
private:
    Compare _cmp;

public:
    explicit CompareExpr(const Expr* lhs, const Expr* rhs, Compare cmp) : BinExpr(lhs, rhs), _cmp(cmp) { }

    Compare getCompare() const {
        return _cmp;
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class NullExpr : public Expr {
public:
    NullExpr() = default;

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class ArrayExpr : public Expr {
private:
    std::unique_ptr<Array<const Expr>> _exp;

public:
    void addExpr(const Expr*);

    const Array<const Expr>* getExpr() const {
        return _exp.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class VarExpr : public Expr {
private:
    std::unique_ptr<const VarDecl> _var;

public:
    explicit VarExpr(const VarDecl*);

    const VarDecl* getVar() const {
        return _var.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class PropertyExpr : public Expr {
private:
    static const std::unordered_map<std::string, std::string> Properties;

    const std::string _property;
    std::unique_ptr<const Expr> _exp;

public:
    explicit PropertyExpr(const std::string& prop, const Expr* exp) : _property(prop), _exp(exp) { }

    const std::string& getProperty() const;

    const Expr* getExpr() const {
        return _exp.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

#endif
