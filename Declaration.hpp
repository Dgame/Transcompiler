#ifndef DECL_HPP
#define DECL_HPP

#include "Type.hpp"
#include "Visitor.hpp"
#include "Instruction.hpp"
#include "Array.hpp"
#include "Scope.hpp"
#include "Expression.hpp"

class Decl : public Instruction { };

class VarDecl : public Decl {
private:
    std::shared_ptr<const Type> _type;
    std::unique_ptr<const Expr> _exp;

    std::string _name;

    const VarDecl* _parent = nullptr;

public:
    explicit VarDecl(const std::string& name, std::shared_ptr<const Type> type, const Expr* exp) : _type(type), _exp(exp), _name(name) { }
    explicit VarDecl(const VarDecl* parent, const Expr* exp) : _name(parent->getName()), _exp(exp), _parent(parent) { }

    const VarDecl* getParent() const {
        return _parent;
    }

    const Type* getType() const;

    const Expr* getExpr() const {
        return _exp.get();
    }

    const std::string& getName() const {
        return _name;
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class PrintDecl : public Decl {
private:
    std::unique_ptr<const StringExpr> _fmt;
    std::unique_ptr<Array<const Expr>> _exprs;

public:
    PrintDecl() = default;
    explicit PrintDecl(const StringExpr* fmt) : _fmt(fmt) { }

    void addExpr(const Expr*);

    const Array<const Expr>* getExpr() const {
        return _exprs.get();
    }

    const StringExpr* getFormat() const {
        return _fmt.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class Parameter : public Decl {
private:
    const std::string _name;
    std::shared_ptr<const Type> _type;

public:
    explicit Parameter(const std::string& name, std::shared_ptr<const Type> type) : _name(name), _type(type) { }
    explicit Parameter(std::shared_ptr<const Type> type) : _type(type) { }

    const Type* getType() const {
        return _type.get();
    }

    const std::string& getName() const {
        return _name;
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class Return : public Decl {
private:
    std::unique_ptr<const Expr> _exp;

public:
    explicit Return(const Expr* exp) : _exp(exp) { }

    const Expr* getExpr() const {
        return _exp.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class FuncDecl : public Decl {
private:
    const std::string _name;
    std::shared_ptr<const Type> _type;
    std::unique_ptr<const Scope> _scope;
    std::unique_ptr<Array<const Parameter>> _parameter;

public:
    explicit FuncDecl(const std::string& name, std::shared_ptr<const Type> type) : _name(name), _type(type) { }

    void addParameter(const Parameter*);

    const Array<const Parameter>* getParameter() const {
        return _parameter.get();
    }

    const std::string& getName() const {
        return _name;
    }

    const Type* getType() const {
        return _type.get();
    }

    void setScope(const Scope* sc) {
        _scope = std::unique_ptr<const Scope>(sc);
    }

    const Scope* getScope() const {
        return _scope.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

#endif
