#include <iostream>
#include <string>
#include "Lexer.h"

int main()
{

        std::string filename ="H:/Lexer/input/main.txt";
        Lexer* lex = new Lexer(const_cast<char*>(filename.c_str()));

        lex->printSequenceOfTokens();
        lex->generateHTML();

        delete lex;

    return 0;
}
