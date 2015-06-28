#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <map>
#include "type_alias.hpp"

enum class TokenType {
    None,
    Eof,
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
    Underscore,
    Comma,
    Semicolon,
    Colon,
    Question,
    Not,
    Tilde,
    Hash,
    LArrow, // <-
    RArrow, // ->
    DoubleArrow, // =>
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

bool isOperator(TokenType);
bool isOperation(TokenType);
bool isBoolean(TokenType);

const std::map<const std::string, Keyword> Keywords = {
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

Keyword isKeyword(const std::string&);

struct Cursor {
    const char* ptr = nullptr;
    u32_t line = 1;
    u16_t column = 1;

    Cursor& next();
};

struct Token {
    TokenType type;
    Cursor cursor;

    union {
        i32_t ival;
        f32_t fval;
        Keyword keyword;
    };

    std::string id;

    Token() = default;
    explicit Token(TokenType ty, Cursor loc) : type(ty), cursor(loc) { }
};

#endif
