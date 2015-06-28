#include <iostream>
#include "Lexer.hpp"

int main() {
    Lexer lex("{ print 4.21 }");
    while (true) {
        const Token tok = lex.get();
        if (tok.type == TokenType::None || tok.type == TokenType::Eof)
            break;

        std::cout << static_cast<u16_t>(tok.type) << ':' << *tok.cursor.ptr << std::endl;
        switch (tok.type) {
            case TokenType::Integer:
                printf("%d\n", tok.ival);
            break;
            case TokenType::Float:
                printf("%f\n", tok.fval);
            break;
            case TokenType::Identifier:
            case TokenType::Keyword:
                printf("%s\n", &tok.id.front());
            break;
        }
    }
}
