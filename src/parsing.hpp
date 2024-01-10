#ifndef PARSING_HPP
#define PARSING_HPP

#include "includes.hpp"

//All the types of tokens accepted
enum class TokenType {
    _exit,
    _int_lit,
    _semi,
    _open_paren,
    _close_paren,
    _stdout,
    _eq,
    _strType,
    _intType,
    _str,
    _int,
};
// a structure for a combination of tokentype and a value for it, which is optional
struct Token {
    TokenType type;
    std::optional<std::string> value {};
};
//this is the class that has all the methods to parse the code into tokens
class CodeParser
{
public:
    std::vector<Token> parse(std::string* content, int len);
};
#endif