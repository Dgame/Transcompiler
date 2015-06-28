#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <unordered_map>

enum class TokenType {
    None,
    Integer,
    Float,
    Identifier,
    Keyword,
    Plus,
    Minus,
    Mul,
    Div,
    Percent,
    BitAnd,
    BitOr,
    LogicAnd,
    LogicOr,
    DoubleQuote,
    SingleQuote,
    Assign,
    Equal,
    NotEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,
    Dot,
    Comma,
    Semicolon,
    Colon,
    Question,
    Not,
    Tilde,
    Hash,
    LParen, // (
    RParen, // )
    LBracket, // [
    RBracket, // ]
    LCurly, // {
    RCurly // }
};

enum class Keyword {
    None,
    Print,
    If,
    Else,
    ElseIf,
    Switch,
    Return,
    For,
    Import,
    In,
    Let,
    Const,
    True,
    False,
};

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

const std::unordered_map<const char*, Keyword> Keywords = {
    {"print", Keyword::Print},
    {"if", Keyword::If},
    {"else", Keyword::Else},
    {"elif", Keyword::ElseIf},
    {"switch", Keyword::Switch},
    {"return", Keyword::Return},
    {"for", Keyword::For},
    {"import", Keyword::Import},
    {"in", Keyword::In},
    {"let", Keyword::Let},
    {"const", Keyword::Const},
    {"true", Keyword::True},
    {"false", Keyword::False},
};

Keyword isKeyword(const char* kw) {
    auto it = Keywords.find(kw);
    if (it != Keywords.end())
        return it->second;
    return Keyword::None;
}

struct Cursor {
    const char* ptr = nullptr;
    u32_t line = 0;
    u16_t column = 0;
};

struct Token {
    TokenType type;
    Cursor cursor;

    union {
        i32_t ival;
        f32_t fval;
        const char* identifier;
    }

    Token() = default;
    explicit Token(TokenType ty, Cursor loc) : type(ty), cursor(loc) { }
};

#endif
