#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include "type_alias.hpp"
#include "Token.hpp"

class Lexer {
private:
    Cursor _cursor;
    std::vector<Token> _tokens;

    void _readNumber();
    void _readIdentifier();
    void _lex();

public:
    explicit Lexer(const char*);

    const Token* begin() const {
        return &_tokens.front();
    }

    const Token* end() const {
        return &_tokens.back();
    }

    u32_t count() const {
        return _tokens.size();
    }
};

#endif
