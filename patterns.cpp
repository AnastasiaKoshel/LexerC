#include "patterns.h"

std::set<std::string> patterns::directives = {	"#include", "#define", "#if", "#ifdef","#elif",
												"#else", "#endif", "#warning", "#error", "#undef",
												"#ifndef", "#line", "#pragma" };

std::set<std::string> patterns::keywords = {	"alignas","alignof","auto",
                                                "bool","break","case","char",
                                                "complex","const","constexpr","continue",
                                                "default","do","double","else","enum",
                                                "extern","false","float","for","goto",
                                                "if","inline","int","long",
                                                "nullptr","register","restrict","return",
                                                "short","signed","sizeof","static",
                                                "struct","switch","true","typedef","union",
                                                "unsigned","void","volatile","while"};


std::set<char> patterns::punctuation = {		'!','%','^','&','*','(',')','-','+','=','{','}','|','~','[',']',
                                                ';',':','"','<','>','?',',','.','/','#',' ','\n'};
