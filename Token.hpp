#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <unordered_map>
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
    U_64,
    U_32,
    U_16,
    U_8,
    I_64,
    I_32,
    I_16,
    I_8,
    Bool,
    Char,
    F_64,
    F_32,
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

const std::unordered_map<std::string, Keyword> Keywords = {
    {"u64", Keyword::U_64},
    {"u32", Keyword::U_32},
    {"u16", Keyword::U_16},
    {"u8", Keyword::U_8},
    {"i64", Keyword::I_64},
    {"i32", Keyword::I_32},
    {"i16", Keyword::I_16},
    {"i8", Keyword::I_8},
    {"bool", Keyword::Bool},
    {"char", Keyword::Char},
    {"f64", Keyword::F_64},
    {"f32", Keyword::F_32},
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
        u64_t uival;
        i64_t sival;
        f64_t fval;
        Keyword keyword;
    };

    std::string id;

    Token() = default;
    explicit Token(TokenType ty, Cursor loc) : type(ty), cursor(loc) { }
};

#endif
