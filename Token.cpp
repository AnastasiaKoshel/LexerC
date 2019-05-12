#include "Token.h"

Token::Token(std::string tokenName, std::string tokenAttribute)
    : name(tokenName),
    attribute(tokenAttribute)
{
    if (tokenName == "identifier")
    {
        if (patterns::isKeyword(tokenAttribute))
        {
            name = "keywords";
        }
    }
    else
        if (tokenName == "directives" && !patterns::isDirective(tokenAttribute))
        {
            name = "error";
        }
}
