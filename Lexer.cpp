#include "Lexer.hpp"

#include "config.hpp"
#if DEBUG
    #include <iostream>
#endif
#include <cmath>

void Lexer::_readIdentifier(Token* tok) {
    const Cursor loc = _cursor;

    u16_t n = 0;
    for (; std::isalnum(*_cursor.ptr); n++) {
        _cursor.next();
    }

    const std::string id = std::string(loc.ptr, n);
    const Keyword kw = isKeyword(id);
    const TokenType toktype = (kw == Keyword::None) ? TokenType::Identifier : TokenType::Keyword;

    *tok = Token(toktype, loc);
    tok->id = id;
    tok->keyword = kw;
}

void Lexer::_readNumber(Token* tok) {
    const Cursor loc = _cursor;

    bool neg = false;
    if (*_cursor.ptr == '-') {
        _cursor.next();
        neg = true;
    }

    u16_t n = 0;
    u64_t ival = 0;
    for (; std::isdigit(*_cursor.ptr); n++) {
        ival *= 10;
        ival += (*_cursor.ptr) - '0';

        _cursor.next();
        if (*(_cursor.ptr) == '_' &&
            std::isdigit(*(_cursor.ptr + 1)))
        {
            _cursor.next();
        }
    }

    if (*_cursor.ptr == '.') {
        _cursor.next();

        for (; std::isdigit(*_cursor.ptr); n++) {
            ival *= 10;
            ival += (*_cursor.ptr) - '0';

            _cursor.next();
            if (*(_cursor.ptr) == '_' &&
                std::isdigit(*(_cursor.ptr + 1)))
            {
                _cursor.next();
            }
        }

        *tok = Token(TokenType::Float, loc);
        tok->fval = ival / std::pow(10, n - 1);

        if (neg)
            tok->fval *= -1;
    } else {
        *tok = Token(TokenType::Integer, loc);
        tok->ival = ival;

        if (neg)
            tok->ival *= -1;
    }
}

Lexer::Lexer(const std::string& content) {
    _cursor.ptr = &content[0];
}

Token Lexer::get() {
    Token tok(TokenType::None, _cursor);

    switch (*_cursor.ptr) {
        case 0:
            tok = Token(TokenType::Eof, _cursor);
        break;
        case 9: // tab
        case 11: // vtab
        case 32: // space
            _cursor.next();
            return get();
        break;
        case 'a' ... 'z':
            _readIdentifier(&tok);
            return tok;
        case '0' ... '9':
            _readNumber(&tok);
            return tok;
        case '\'':
            tok = Token(TokenType::SingleQuote, _cursor);
        break;
        case '"':
            tok = Token(TokenType::DoubleQuote, _cursor);
        break;
        case '+':
            tok = Token(TokenType::Plus, _cursor);
        break;
        case '-':
        {
            if (std::isdigit(*(_cursor.ptr + 1))) {
                _readNumber(&tok);
                return tok;
            }

            const Cursor loc = _cursor;
            if (*(_cursor.ptr + 1) == '>') {
                _cursor.next();
                tok = Token(TokenType::RArrow, _cursor);
            } else
                tok = Token(TokenType::Minus, _cursor);
        }
        break;
        case '*':
            tok = Token(TokenType::Mul, _cursor);
        break;
        case '/':
            tok = Token(TokenType::Div, _cursor);
        break;
        case '%':
            tok = Token(TokenType::Percent, _cursor);
        break;
        case '&':
        {
            const Cursor loc = _cursor;
            if (*(_cursor.ptr + 1) == '&') {
                _cursor.next();
                tok = Token(TokenType::LogicAnd, loc);
            } else
                tok = Token(TokenType::BitAnd, loc);
        }
        break;
        case '|':
        {
            const Cursor loc = _cursor;
            if (*(_cursor.ptr + 1) == '|') {
                _cursor.next();
                tok = Token(TokenType::LogicOr, loc);
            } else
                tok = Token(TokenType::BitOr, loc);
        }
        break;
        case '!':
        {
            const Cursor loc = _cursor;
            if (*(_cursor.ptr + 1) == '=') {
                _cursor.next();
                tok = Token(TokenType::NotEqual, _cursor);
            } else
                tok = Token(TokenType::Not, _cursor);
        }
        break;
        case '?':
            tok = Token(TokenType::Question, _cursor);
        break;
        case '_':
            tok = Token(TokenType::Underscore, _cursor);
        break;
        case ':':
            tok = Token(TokenType::Colon, _cursor);
        break;
        case ';':
            tok = Token(TokenType::Semicolon, _cursor);
        break;
        case ',':
            tok = Token(TokenType::Comma, _cursor);
        break;
        case '.':
            tok = Token(TokenType::Dot, _cursor);
        break;
        case '#':
            tok = Token(TokenType::Hash, _cursor);
        break;
        case '~':
            tok = Token(TokenType::Tilde, _cursor);
        break;
        case '{':
            tok = Token(TokenType::LCurly, _cursor);
        break;
        case '}':
            tok = Token(TokenType::RCurly, _cursor);
        break;
        case '(':
            tok = Token(TokenType::LParen, _cursor);
        break;
        case ')':
            tok = Token(TokenType::RParen, _cursor);
        break;
        case '[':
            tok = Token(TokenType::LBracket, _cursor);
        break;
        case ']':
            tok = Token(TokenType::RBracket, _cursor);
        break;
        case '>':
        {
            const Cursor loc = _cursor;
            if (*(_cursor.ptr + 1) == '=') {
                _cursor.next();
                tok = Token(TokenType::GreaterEqual, _cursor);
            } else
                tok = Token(TokenType::Greater, _cursor);
        }
        break;
        case '<':
        {
            const Cursor loc = _cursor;
            if (*(_cursor.ptr + 1) == '-') {
                _cursor.next();
                tok = Token(TokenType::LArrow, _cursor);
            } else if (*(_cursor.ptr + 1) == '=') {
                _cursor.next();
                tok = Token(TokenType::LessEqual, _cursor);
            } else
                tok = Token(TokenType::Less, _cursor);
        }
        break;
        case '=':
        {
            const Cursor loc = _cursor;
            if (*(_cursor.ptr + 1) == '=') {
                _cursor.next();
                tok = Token(TokenType::Equal, _cursor);
            } else if (*(_cursor.ptr + 1) == '>') {
                _cursor.next();
                tok = Token(TokenType::DoubleArrow, _cursor);
            } else
                tok = Token(TokenType::Assign, _cursor);
        }
        break;
    }

    if (_cursor.ptr)
        _cursor.next();

    return tok;
}
