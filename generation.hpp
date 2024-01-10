#ifndef GENERATION_HPP
#define GENERATION_HPP

#include "statementize.hpp"

//this is the class that has all the methods to generate code
class CodeGenerator
{
public:
    void generate(std::vector<Statement> statements); // public version of generate
private:
    void gen(); // private version, so we can not use the smaller methods from the main
};
#endif