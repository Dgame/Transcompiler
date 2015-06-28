#include <iostream>
#include "Lexer.hpp"

int main() {
    Lexer lex("print 3.14");
    Token tok = lex.get();
    std::cout << static_cast<u16_t>(tok.type) << ':' << tok.id << std::endl;
    tok = lex.get();
    std::cout << static_cast<u16_t>(tok.type) << ':' << tok.fval << std::endl;
}
