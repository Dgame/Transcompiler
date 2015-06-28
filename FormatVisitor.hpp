#ifndef FORMAT_VISITOR_HPP
#define FORMAT_VISITOR_HPP

#include <ostream>
#include "Visitor.hpp"

class FormatVisitor : public Visitor {
private:
    std::ostream& _out;

public:
    explicit FormatVisitor(std::ostream& stream) : _out(stream) { }

    void visit(const IntExpr*) override {
        _out << "%d";
    }

    void visit(const FloatExpr*) override {
        _out << "%f";
    }

    void visit(const BoolExpr*) override {
        _out << "%d";
    }

    void visit(const CharExpr*) override {
        _out << "%c";
    }

    void visit(const StringExpr*) override {
        _out << "%s";
    }
};

#endif