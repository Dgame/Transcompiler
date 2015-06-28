#include "Token.hpp"

Cursor& Cursor::next() {
    this->column++;
    this->ptr++;

    if (*this->ptr == '\r')
        this->ptr++;

    if (*this->ptr == '\n') {
        this->ptr++;
        this->line++;
    }

    return *this;
}

bool isOperator(TokenType type) {
    switch (type) {
        case TokenType::Plus:
        case TokenType::Minus:
        case TokenType::Mul:
        case TokenType::Div:
        case TokenType::Percent:
            return true;
        default:
            return false;
    }
}

bool isOperation(TokenType type) {
    if (isOperator(type))
        return true;

    switch (type) {
        case TokenType::BitAnd:
        case TokenType::BitOr:
            return true;
        default:
            return false;
    }
}

bool isBoolean(TokenType type) {
    switch (type) {
        case TokenType::LogicAnd:
        case TokenType::LogicOr:
        case TokenType::Equal:
        case TokenType::NotEqual:
        case TokenType::Greater:
        case TokenType::GreaterEqual:
        case TokenType::Less:
        case TokenType::LessEqual:
        case TokenType::Not:
            return true;
        default:
            return false;
    }
}

Keyword isKeyword(const std::string& kw) {
    auto it = Keywords.find(kw);
    if (it != Keywords.end())
        return it->second;
    return Keyword::None;
}
