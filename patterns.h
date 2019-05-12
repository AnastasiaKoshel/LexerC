#pragma once

#include <string>
#include <set>

class patterns
{
    static std::set<std::string> directives, keywords;
	static std::set<char> punctuation;

public:
	static bool isDirective(std::string word)
	{
		return directives.find(word) != directives.end();
	}

	static bool isKeyword(std::string word)
	{
        return keywords.find(word) != keywords.end();
	}

    static bool isPunctuation(char word)
	{
		return punctuation.find(word) != punctuation.end();
	}
};
