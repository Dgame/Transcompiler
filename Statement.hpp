#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "Visitor.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"
#include "Scope.hpp"

class Stmt : public Instruction { };

class IfStmt : public Stmt {
private:
    std::unique_ptr<const Expr> _exp;
    std::unique_ptr<const Scope> _scope;

public:
    explicit IfStmt(const Expr* exp, const Scope* scope) : _exp(exp), _scope(scope) { }

    const Expr* getExpr() const {
        return _exp.get();
    }

    const Scope* getScope() const {
        return _scope.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class ImportStmt : public Stmt {
private:
    const std::unique_ptr<const StringExpr> _import;

public:
    explicit ImportStmt(const StringExpr* import) : _import(import) { }

    const StringExpr* getExpr() const {
        return _import.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class ForLoopStmt : public Stmt {
private:
    std::unique_ptr<const VarDecl> _init;
    std::unique_ptr<const Expr> _cond;
    std::unique_ptr<const VarDecl> _loop;
    std::unique_ptr<const Scope> _scope;

public:
    explicit ForLoopStmt(const VarDecl* init, const Expr* cond, const VarDecl* loop, const Scope* scope) : _init(init), _cond(cond), _loop(loop), _scope(scope) { }

    const VarDecl* getInitVar() const {
        return _init.get();
    }

    const Expr* getCondExpr() const {
        return _cond.get();
    }

    const VarDecl* getLoopVar() const {
        return _loop.get();
    }

    const Scope* getScope() const {
        return _scope.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

class ForEachLoopStmt : public Stmt {
private:
    std::unique_ptr<const VarDecl> _var;
    std::unique_ptr<const Expr> _exp;
    std::unique_ptr<const Scope> _scope;

public:
    explicit ForEachLoopStmt(const VarDecl* var, const Expr* exp, const Scope* scope) : _var(var), _exp(exp), _scope(scope) { }

    const VarDecl* getVar() const {
        return _var.get();
    }

    const Expr* getExpr() const {
        return _exp.get();
    }

    const Scope* getScope() const {
        return _scope.get();
    }

    virtual void accept(Visitor* v) const {
        v->visit(this);
    }
};

#endif
