#pragma once

#include <string>
#include "patterns.h"

class Token
{
    std::string name;
    std::string attribute;

public:
    Token(std::string tokenName, std::string tokenAttribute = "");

    std::string getName()       const { return name; }
    std::string getAttribute()  const { return attribute; }
};
