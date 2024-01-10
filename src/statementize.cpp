//
// This file is to take in the tokens after parsing, and convert them into groups, which can be sent back as statements, for example a group for printing something. it also checks if the order of the tokens is correct
//

#include "statementize.hpp"

std::vector<Statement> CodeStatementizer::statementize(std::vector<Token> tokens) // The main function which takes in an array of tokens
{
    std::vector<Statement> statements; // this array of statements will be returned

    for (int i = 0; i < tokens.size(); i++) // this loops through all of the tokens
    {
        if (tokens[i].type == TokenType::_exit) // checks if the 1st token is exit
        {
            // if it is, then it chechs for the correct structure, which would be (int);
            if (tokens[i+1].type == TokenType::_open_paren 
            && tokens[i+2].type == TokenType::_int
            && tokens[i+3].type == TokenType::_close_paren 
            && tokens[i+4].type == TokenType::_semi)
            {
            if (tokens[i+2].value.has_value()) // this is just good practice, to check if tthe optional has value before trying to access it
            {
                // if it is the correct order, then add a statement to the list, with the int as the value
                statements.push_back({.type = StatementType::_exit, .value = tokens[i+2].value.value()});
                i+=4; // going forward 4, since weve already checked those
            }
            }
            else
            {
                std::perror("Invalid Exit Syntax"); // if it starts with exit, but the order isnt correct, then error
            }
        }
        else if(tokens[i].type == TokenType::_stdout) // this checks if the first one is a standard output instruction
        {
            //checking for correct order
            if (tokens[i+1].type == TokenType::_open_paren 
            && tokens[i+2].type == TokenType::_str
            && tokens[i+3].type == TokenType::_close_paren 
            && tokens[i+4].type == TokenType::_semi)
            {
                if (tokens[i+2].value.has_value()) // good practice
                {
                    statements.push_back({.type = StatementType::_stdout, .value = tokens[i+2].value.value()}); // adding it to the array, with the string as a value
                    i+=4; // going forward the ones that weve already checked
                }
            }
            else
            {
                std::perror("Invalid STDOUT Syntax"); // if it starts with stdout, but the order isnt correct, then error
            }
        }
    }
    return statements;
}
