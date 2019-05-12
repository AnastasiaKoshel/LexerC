#pragma once

#include <iostream>
#include <list>
#include<string>
#include "Tape.h"
#include "Token.h"
#include "patterns.h"

class Lexer
{
    Tape tape;
    std::list<Token> tokens;

    std::string outputFilename;

private:
	Lexer();
    Lexer(const Lexer&);
	Lexer& operator=(const Lexer&);

private:
    Token getToken(std::string buffer, char symbol, int state, bool error = false);

public:
    Lexer(char* filename);

    void  printSequenceOfTokens();
	void  generateHTML();
};
