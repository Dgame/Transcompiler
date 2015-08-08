#ifndef PARSER_HPP
#define PARSER_HPP

class Parser {
private:
    Lexer _lex;

public:
    explicit Parser(Lexer);

    void parse();
};

#endif
