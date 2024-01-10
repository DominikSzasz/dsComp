//
// This file is to parse the code from character by character, then assign a token to all of the characters
//

#include "parsing.hpp"

//this is the main function in this file, which parses the code
std::vector<Token> CodeParser::parse(std::string* content, int len) // takes in the entire file as a string, and the length of it
{
    std::vector<Token> tokens; // creates the array of tokens which will be returned
    std::string buf; // a basic buffer which will be used for multi character tokens, like keywords, or strings
    for (std::size_t i = 0; i < content->size(); ++i) { // looping through entire file char by char
        char ch = (*content)[i]; // assigning a var to the current char
        // Check if the character is alphanumeric
        if (std::isalpha(ch)) {
            buf.clear(); //clear the buf from previous use
            buf += ch; // add first char to buf
            while (i + 1 < content->size() && std::isalnum((*content)[i + 1])) { // advancing forward, while the char is an alpha numeric
                buf += (*content)[i + 1]; // adding each digit to the buffer
                ++i;
            }
            if(buf == "exit") // exit keyword
                {
                    tokens.push_back({.type = TokenType::_exit}); // add to tokens an exit token
                    buf.clear();
                    
                }
            else if(buf == "str")
            {
                tokens.push_back({.type = TokenType::_strType});
                buf.clear();
            }
            else if(buf == "int")
            {
                tokens.push_back({.type = TokenType::_intType});
                buf.clear();
            }
            else if(buf == "stdout")
            {
                tokens.push_back({.type = TokenType::_stdout});
                buf.clear();
            }
        }
        else if (ch == '(')
            tokens.push_back({.type = TokenType::_open_paren});
        
        else if (ch == ')')
            tokens.push_back({.type = TokenType::_close_paren});

        else if (ch == '=')
            tokens.push_back({.type = TokenType::_eq});
    
        else if (ch == ';')
            tokens.push_back({.type = TokenType::_semi});
        
        else if (std::isdigit(ch))
        {
            buf.clear();
            buf += ch;
            if(isdigit((*content)[i + 1]))
            {
                while (i + 1 < content->size() && std::isdigit((*content)[i + 1])) {
                ++i;
                buf += (*content)[i];
            }
            }
            
            tokens.push_back({.type = TokenType::_int, .value = buf});
            continue;
        }
        else if(ch == '"')
        {
            i++;
            buf.clear();
            while((*content)[i] != '"')
            {
                buf += (*content)[i];
                i++;
            }
            tokens.push_back({.type = TokenType::_str, .value=buf});
        }
    }
    //the above code, before the other comment, basically does the same, checks for a token, adds it to the array
    return tokens;
};
