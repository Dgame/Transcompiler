#ifndef LEXER_HPP
#define LEXER_HPP

#include "type_alias.hpp"
#include "Token.hpp"

class Lexer {
private:
    Cursor _cursor;

    void _readIdentifier(Token*);
    void _readNumber(Token*);

public:
    explicit Lexer(const std::string&);

    Token get();
};

#endif
