#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <vector>

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
enum class StatementType {
    _stdout,
    _exit,
    _int,
    _str,
};
struct Token {
    TokenType type;
    std::optional<std::string> value {};
};
struct Statement {
    StatementType type;
    std::optional<std::string> value {};
};
void generate(std::string* asmcode);
std::vector<Token> parse(std::string* content, int len);
std::vector<Statement> statementize(std::vector<Token> tokens);

std::string genExit(int returnval);
std::string genSTDOUT(std::string val);
std::string genVar(std::string val);
int main() {
    std::string line;
    std::string content;
    std::ifstream file("input.ds");
    if (file.is_open()) {
        while (getline(file, line)) {
            if(line[0] != '#')
            {
                content += line;
            }
        }
        file.close();
    }
    std::vector<Token> parsed = parse(&content, content.size());
    statementize(parsed);
    //generate(&content);
    return 0;
}
std::vector<Statement> statementize(std::vector<Token> tokens)
{
    std::vector<Statement> statements;
    for (int i = 0; i < tokens.size(); i++)
    {

        //std::cout << "Token Type: " << static_cast<int>(tokens[i].type) << std::endl;
        if (tokens[i].type == TokenType::_exit)
        {
            // std::cout << "Token Type: " << static_cast<int>(tokens[i].type) << std::endl;

            if (tokens[i+1].type == TokenType::_open_paren 
            && tokens[i+2].type == TokenType::_int
            && tokens[i+3].type == TokenType::_close_paren 
            && tokens[i+4].type == TokenType::_semi)
            {
            if (tokens[i+2].value.has_value()) 
            {
                statements.push_back({.type = StatementType::_exit, .value = tokens[i+2].value.value()});
                i+=4;
            }
            }
            else
            {
                std::perror("Invalid Exit Syntax");
            }
        }

    }
    for (const auto& statement : statements) {
        std::cout << "Statement Type: " << static_cast<int>(statement.type) << std::endl;
    }
    return statements;
}
std::vector<Token> parse(std::string* content, int len)
{
    std::vector<Token> tokens;
    std::string buf;
    for (std::size_t i = 0; i < content->size(); ++i) {
        char ch = (*content)[i];
        // Check if the character is alphanumeric
        if (std::isalpha(ch)) {
            // Print the current character
            buf.clear();
            buf += ch;
            // Continue printing while the next character is alphanumeric
            while (i + 1 < content->size() && std::isalnum((*content)[i + 1])) {
                buf += (*content)[i + 1];
                ++i;
            }
            if(buf == "exit")
                {
                    tokens.push_back({.type = TokenType::_exit});
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
            // else if(ch.size() > 0)
            // {
            //     std::cout << buf;
            //     std:perror("Token Not Found");
            // }
            
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
    }

    // for (const auto& token : tokens) {
    //     std::cout << "Token Type: " << static_cast<int>(token.type) << std::endl;
    // }
    return tokens;
}
void generate(std::string* asmcode)
{
    std::string sectiondata = "section .data\n";
    std::string sectionbss = "section .bss\n";
    std::string sectiontext = "section .text\n\tglobal _main\n_main:\n";
    sectiondata += genVar("Hello");
    sectiontext += genSTDOUT("Hello");
    sectiontext += genExit(0);
    std::ofstream outputFile("out.asm");

        // Check if the file is successfully opened
        if (outputFile.is_open()) {
            outputFile << sectiondata;
            outputFile << sectionbss;
            outputFile << sectiontext;
            // Close the file
            outputFile.close();

            std::cout << "Generated.\n";
        } else {
            std::cerr << "Unable to open the file.\n";
        }
        return;
    }
std::string genExit(int returnval)
{
    std::string output = "\tmov rax, 0x02000001\n\tmov rdi, " + std::to_string(returnval) + "\n\tsyscall\n";
    return output;
}
std::string genSTDOUT(std::string varname)
{
    std::string output = "\tmov rax, 0x02000004\n\tmov rdi, 1\n\tmov rsi, " + varname + "\n\tmov rdx, " + std::to_string(varname.size()) + "\n\tsyscall\n";
    return output;
}
std::string genVar(std::string val)
{
    std::string output = "\t" + val + ": db \""+ val +"\", 10\n";
    return output;
}