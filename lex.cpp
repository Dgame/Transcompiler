#include <iostream>
#include "Lexer.hpp"

int main() {
    Lexer lex("main() { print 4.21 }");
    while (true) {
        const Token tok = lex.get();
        if (tok.type == TokenType::None || tok.type == TokenType::Eof)
            break;

        switch (tok.type) {
            case TokenType::Integer:
                printf("\tint: %d\n", tok.ival);
            break;
            case TokenType::Float:
                printf("\tfloat: %f\n", tok.fval);
            break;
            case TokenType::Identifier:
            case TokenType::Keyword:
                printf("\tid or kw: %s\n", &tok.id.front());
            break;
            default:
                std::cout << static_cast<u16_t>(tok.type) << ':' << *tok.cursor.ptr << std::endl;
        }
    }
}
