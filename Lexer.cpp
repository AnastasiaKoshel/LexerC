#include "Lexer.h"

Lexer::Lexer(char* filename)
    : tape(filename),
    outputFilename("result.html")
{

    while (!tape.empty())
    {
        tokens.push_back(getToken("", tape.first(), 0));
    }
}

Token Lexer::getToken(std::string buffer, char symbol, int state, bool error)
{
    int nextState = state;

    switch (state)
    {
        case 0: //non-terminal state
        {
            if (symbol >= '1' && symbol <= '9')
            {
                nextState = 3;
            }
            else
                if ((symbol >= 'a' && symbol <= 'z') ||
                    (symbol >= 'A' && symbol <= 'Z') ||
                    (symbol == '_'))
                {
                    nextState = 32;
                }
                else
                {
                    if ((symbol == '=') ||
                        (symbol == '*') ||
                        (symbol == '!') ||
                        (symbol == '%') ||
                        (symbol == '^'))
                    {
                        nextState = 17;
                    }
                    else
                    {
                        if ((symbol == '(') || (symbol == ')') ||
                            (symbol == '[') || (symbol == ']') ||
                            (symbol == '{') || (symbol == '}') ||
                            (symbol == '~') || (symbol == '?'))
                        {
                            nextState = 18;
                        }
                        else
                        {
                            switch (symbol)
                            {
                                case '.':
                                    nextState = 1;
                                break;

                                case '0':
                                    nextState = 9;
                                break;

                                case '/':
                                    nextState = 22;
                                break;
                                case '+':
                                    nextState = 28;
                                break;

                                case '&':
                                    nextState = 21;
                                break;

                                case '-':
                                    nextState = 19;
                                break;

                                case '|':
                                    nextState = 27;
                                break;

                                case '<':
                                    nextState = 29;
                                break;

                                case '>':
                                    nextState = 31;
                                break;

                                case ':':
                                    nextState = 33;
                                break;

                                case '\'':
                                    nextState = 34;
                                break;

                                case '\"':
                                    nextState = 38;
                                break;

                                case '#':
                                    nextState = 40;
                                break;

                                default:
                                    if (patterns::isPunctuation(symbol))
                                    {
                                        tape.pop();
                                        return Token("punctuation",buffer+symbol);
                                    }
                                    else
                                        error = true;
                                break;
                            }
                        }
                    }
                }
        }
        break;

        case 1: //terminal state
        {
            if (symbol >= '0' && symbol <= '9')
                nextState = 2;
            else
            {
                return Token("operator",buffer);
            }
        }
        break;

        case 2: //terminal state
        {
            if (symbol >= '0' && symbol <= '9')
                nextState = 2;
            else
            {
                if (symbol == 'f' || symbol == 'F' ||
                    symbol == 'l' || symbol == 'L')
                {
                    nextState = 5;
                }
                else
                {
                    if (symbol == 'e' || symbol == 'E')
                        nextState = 6;
                    else
                    {
                        // check for terminal state
                        if (patterns::isPunctuation(symbol))
                            return Token(error ? "error" : "number",buffer);
                        error = true;
                    }
                }
            }
        }
        break;

        case 3: //terminal state
        {
            if (symbol >= '0' && symbol <= '9')
                nextState = 3;
            else
            {
                if (symbol == '.')
                    nextState = 4;
                else
                {
                    if (symbol == 'u' || symbol == 'U')
                        nextState = 13;
                    else
                    {
                        if (symbol == 'l' || symbol == 'L')
                            nextState = 14;
                        else
                        {
                            // check for terminal state
                            if (patterns::isPunctuation(symbol))
                                return Token(error ? "error" : "number",buffer);
                            error = true;
                        }
                    }
                }
            }
        }
        break;

        case 4: //terminal state
        {
            if (symbol >= '0' && symbol <= '9')
                nextState = 2;
            else
            {
                // check for terminal state
                if (patterns::isPunctuation(symbol))
                    return Token(error ? "error" : "number",buffer);
                error = true;
            }
        }
        break;

        case 5: //terminal state
        {
            // check for terminal state
            if (patterns::isPunctuation(symbol))
                return Token(error ? "error" : "number",buffer);
            error = true;
        }
        break;

        case 6: //non-terminal state
        {
            if (symbol >= '0' && symbol <= '9')
                nextState = 7;
            else
            {
                if (symbol == '+' || symbol == '-')
                    nextState = 8;
                else
                {
                    if (patterns::isPunctuation(symbol))
                        return Token("error",buffer);

                    error = true;
                }
            }
        }
        break;

        case 7: //terminal state
        {
            if (symbol >= '0' && symbol <= '9')
                nextState = 7;
            else
            {
                // check for terminal state
                if (patterns::isPunctuation(symbol))
                    return Token(error ? "error" : "number",buffer);
                error = true;
            }
        }
        break;

        case 8: //non-terminal state
        {
            if (symbol >= '0' && symbol <= '9')
                nextState = 7;
            else
            {
                if (patterns::isPunctuation(symbol))
                    return Token("error",buffer);

                error = true;
            }
        }
        break;

        case 9: //terminal state
        {
            if (symbol >= '0' && symbol <= '7')
                nextState = 10;
            else
            {
                if (symbol == 'x' || symbol == 'X')
                    nextState = 11;
                else
                {
                    if (symbol == 'b' || symbol == 'B')
                        nextState = 15;
                    else
                    {
                        // check for terminal state
                        if (patterns::isPunctuation(symbol))
                            return Token(error ? "error" : "number",buffer);
                        error = true;
                    }
                }
            }
        }
        break;

        case 10: //terminal state
        {
            if (symbol >= '0' && symbol <= '7')
                nextState = 10;
            else
            {
                if (symbol == 'u' || symbol == 'U')
                    nextState = 13;
                else
                {
                    if (symbol == 'l' || symbol == 'L')
                        nextState = 14;
                    else
                    {
                        // check for terminal state
                        if (patterns::isPunctuation(symbol))
                            return Token(error ? "error" : "number",buffer);
                        error = true;
                    }
                }
            }
        }
        break;

        case 11: //non-terminal state
        {
            if ((symbol >= '0' && symbol <= '9') ||
                (symbol >= 'a' && symbol <= 'f') ||
                (symbol >= 'A' && symbol <= 'F'))
            {
                nextState = 12;
            }
            else
            {
                if (patterns::isPunctuation(symbol))
                    return Token("error",buffer);

                error = true;
            }
        }
        break;

        case 12: //terminal state
        {
            if ((symbol >= '0' && symbol <= '9') ||
                (symbol >= 'a' && symbol <= 'f') ||
                (symbol >= 'A' && symbol <= 'F'))
            {
                nextState = 12;
            }
            else
            {
                if (symbol == 'u' || symbol == 'U')
                    nextState = 13;
                else
                {
                    if (symbol == 'l' || symbol == 'L')
                        nextState = 14;
                    else
                    {
                        // check for terminal state
                        if (patterns::isPunctuation(symbol))
                            return Token(error ? "error" : "number",buffer);
                        error = true;
                    }
                }
            }
        }
        break;

        case 13: //terminal state
        {
            if (symbol == 'l' || symbol == 'L')
                nextState = 5;
            else
            {
                // check for terminal state
                if (patterns::isPunctuation(symbol))
                    return Token(error ? "error" : "number",buffer);
                error = true;
            }
        }
        break;

        case 14: //terminal state
        {
            if (symbol == 'u' || symbol == 'U')
                nextState = 5;
            else
            {
                // check for terminal state
                if (patterns::isPunctuation(symbol))
                    return Token(error ? "error" : "number",buffer);
                error = true;
            }
        }
        break;

        case 15: //non-terminal state
        {
            if (symbol == '0' || symbol == '1')
                nextState = 16;
            else
            {
                if (patterns::isPunctuation(symbol))
                    return Token("error",buffer);

                error = true;
            }
        }
        break;

        case 16: //terminal state
        {
            if (symbol == '0' || symbol == '1')
                nextState = 16;
            else
            {
                if (symbol == 'u' || symbol == 'U')
                    nextState = 13;
                else
                {
                    if (symbol == 'l' || symbol == 'L')
                        nextState = 14;
                    else
                    {
                        // check for terminal state
                        if (patterns::isPunctuation(symbol))
                            return Token(error ? "error" : "number",buffer);
                        error = true;
                    }
                }
            }
        }
        break;

        case 17: //terminal state
        {
            if (symbol == '=')
                nextState = 18;
            else
            {
                return Token("operator",buffer);
            }
        }
        break;

        case 18: //terminal state
        {
            return Token("operator",buffer);
        }
        break;

        case 19: //terminal state
        {
            if (symbol == '=' || symbol == '-')
                nextState = 18;
            else
            {
                if (symbol == '>')
                    nextState = 20;
                else
                {
                    return Token("operator",buffer);
                }
            }
        }
        break;

        case 20: //terminal state
        {
            if (symbol == '*')
                nextState = 18;
            else
            {
                return Token("operator",buffer);
            }
        }
        break;

        case 21: //terminal state
        {
            if (symbol == '=' || symbol == '&')
                nextState = 18;
            else
            {
                return Token("operator",buffer);
            }
        }
        break;

        case 22: //terminal state
        {
            if (symbol == '/')
                nextState = 25;
            else
            {
                if (symbol == '*')
                    nextState = 23;
                else
                    return Token("operator",buffer);
            }
        }
        break;

        case 23: //non-terminal state
        {
            if (symbol == '*')
                nextState = 24;
        }
        break;

        case 24: //non-terminal state
        {
            nextState = symbol == '/' ? 26 : 23;
        }
        break;

        case 25: //terminal state
        {
            if (symbol == '\n')
                return Token("comment",buffer);
        }
        break;

        case 26: //terminal state
        {
            return Token("comment",buffer);
        }
        break;

        case 27: //terminal state
        {
            if (symbol == '|' || symbol == '=')
                nextState = 18;
            else
            {
                return Token("operator",buffer);
            }
        }
        break;

        case 28: //terminal state
        {
            if (symbol == '+' || symbol == '=')
                nextState = 18;
            else
            {
                return Token("operator",buffer);
            }
        }
        break;

        case 29: //terminal state
        {
            if (symbol == '=')
                nextState = 18;
            else
            {
                if (symbol == '<')
                    nextState = 30;
                else
                    return Token("operator",buffer);
            }
        }
        break;

        case 30: //terminal state
        {
            if (symbol == '=')
                nextState = 18;
            else
            {
                return Token("operator",buffer);
            }
        }
        break;

        case 31: //terminal state
        {
            if (symbol == '=')
                nextState = 18;
            else
            {
                if (symbol == '>')
                    nextState = 30;
                else
                    return Token("operator",buffer);
            }
        }
        break;

        case 32: //terminal state
        {
            if ((symbol >= 'a' && symbol <= 'z') ||
                (symbol >= 'A' && symbol <= 'Z') ||
                (symbol >= '0' && symbol <= '9') ||
                (symbol == '_'))
            {
                nextState = 32;
            }
            else
            {
                // check for terminal state
                if (patterns::isPunctuation(symbol))
                    return Token(error ? "error" : "identifier",buffer);
                error = true;
            }
        }
        break;

        case 33: //terminal state
        {
            if (symbol == ':')
                nextState = 18;
            else
            {
                return Token("operator",buffer);
            }
        }
        break;

        case 34: //non-terminal state
        {
            if (symbol == '\'')
                nextState = 37;
            else
                if (symbol == '\\')
                    nextState = 35;
                else
                    nextState = 36;
        }
        break;

        case 35: //non-terminal state
        {
            nextState = 36;
        }
        break;

        case 36: //non-terminal state
        {
            if (symbol == '\'')
                nextState = 37;
            else
                {
                    if (patterns::isPunctuation(symbol))
                        return Token("error",buffer);

                    error = true;
                }
        }
        break;

        case 37: //terminal state
        {
            return Token("literal",buffer);
        }
        break;

        case 38: //non-terminal state
        {
            if (symbol == '"')
                nextState = 37;
            else
                if (symbol == '\\')
                    nextState = 39;
        }
        break;

        case 39: //non-terminal state
        {
            nextState = 38;
        }
        break;

        case 40: //terminal state
        {
            if ((symbol >= 'a' && symbol <= 'z') ||
                (symbol >= 'A' && symbol <= 'Z') ||
                (symbol >= '0' && symbol <= '9') ||
                (symbol == '_'))
            {
                nextState = 40;
            }
            else
            {
                // check for terminal state
                if (patterns::isPunctuation(symbol))
                    return Token(error ? "error" : "directives",buffer);
                error = true;
            }
        }
        break;

        default:
        {
            if (patterns::isPunctuation(symbol))
                return Token("error",buffer+"(incorrect state)");

            error = true;
        }
        break;
    }

    tape.pop();
    buffer += symbol;

    return getToken(buffer,tape.first(),nextState,error);
}

void Lexer::printSequenceOfTokens()
{
    for (auto token = tokens.begin(); token != tokens.end(); ++token)
    {
        std::cout << token->getName() << ": " << token->getAttribute() << "\n";
    }
}

void Lexer::generateHTML()
{
    std::ofstream file(outputFilename);
    if (file)
    {
        file << "<!DOCTYPE html>";
        file << "<html>\n";
        file << " <head>\n";
        file << "  <title>Lexer</title>\n";
        file << " </head>\n";
        file << " <body>\n";

        for (auto token = tokens.begin(); token != tokens.end(); ++token)
        {
            if (token->getName() == "number")
            {
                file << "<font color=\"#150F3A\">";
                file << token->getAttribute();
                file << "</font>";
            }
            else
            {
                if (token->getName() == "operator")
                {
                    if (token->getAttribute() == "<")
                    {
                        file << "<font color=\"#E057E5\">";
                        file << "&lt;";
                        file << "</font>";
                    }
                    else
                    {
                        if (token->getAttribute() == ">")
                        {
                            file << "<font color=\"#E057E5\">";
                            file << "&gt;";
                            file << "</font>";
                        }
                        else
                        {
                            if (token->getAttribute() == ">>")
                            {
                                file << "<font color=\"#E057E5\">";
                                file << "&gt;&gt;";
                                file << "</font>";
                            }
                            else
                            {
                                if (token->getAttribute() == "<<")
                                {
                                    file << "<font color=\"#E057E5\">";
                                    file << "&lt;&lt;";
                                    file << "</font>";
                                }
                                else
                                {
                                    file << "<font color=\"#E057E5\">";
                                    file << token->getAttribute();
                                    file << "</font>";
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (token->getName() == "punctuation")
                    {
                        if (token->getAttribute() == "\n")
                            file << "<br>\n";
                        else
                        {
                            if (token->getAttribute() == "\t")
                            {
                                file << "&nbsp";
                            }
                            else
                                file << token->getAttribute();
                        }
                    }
                    else
                    {
                        if (token->getName() == "literal")
                        {
                            file << "<font color=\"#9495E8\">";
                            file << token->getAttribute();
                            file << "</font>";
                        }
                        else
                        {
                            if (token->getName() == "directives")
                            {
                                file << "<font color=\"#80E7Ed\">";
                                file << token->getAttribute();
                                file << "</font>";
                            }
                            else
                            {
                                if (token->getName() == "comment")
                                {
                                    file << "<font color=\"green\">";
                                    file << token->getAttribute();
                                    file << "</font>";
                                }
                                else
                                {
                                    if (token->getName() == "keywords")
                                    {
                                        file << "<font color=\"blue\">";
                                        file << token->getAttribute();
                                        file << "</font>";
                                    }
                                    else
                                    {
                                        if (token->getName() == "identifier")
                                        {
                                            file << "<b>";
                                            file << token->getAttribute();
                                            file << "</b>";
                                        }
                                        else
                                        {
                                            if (token->getName() == "error")
                                            {
                                                file << "<strike>";
                                                file << token->getAttribute();
                                                file << "</strike>";
                                            }
                                            else
                                                file << token->getAttribute();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        file << " </body>\n";
        file << "</html>";

        file.close();
    }
}
