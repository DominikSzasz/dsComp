#ifndef STATEMENTIZE_HPP
#define STATEMENTIZE_HPP

#include "parsing.hpp"

//All the statements accepted
enum class StatementType {
    _stdout,
    _exit,
    _int,
    _str,
};

//a structure for the combination of the statement and an optional value
struct Statement {
    StatementType type;
    std::optional<std::string> value {};
};

//this is the class that has all the methods to group the tokens into structures
class CodeStatementizer
{
public:
    std::vector<Statement> statementize(std::vector<Token> tokens);
};
#endif