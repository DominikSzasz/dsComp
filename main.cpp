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
    _var,
    _eq,
};
struct Token {
    TokenType type;
    std::optional<std::string> value {};
};
void generate(std::string* asmcode);
std::vector<Token> parse(std::string* content, int len);

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
    parse(&content, content.size());
    //generate(&content);
    return 0;
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
            else if(buf == "var")
            {
                tokens.push_back({.type = TokenType::_var});
                buf.clear();
            }
            else if(buf.size() > 0)
            {
                std::cout << buf;
                std:perror("Token Not Found");
            }
                
        }
    }
    // std::cout << buf;
    // if(tokens[0].type == TokenType::_int_lit)
    // {
    //     std::cout << "test";
    for (const auto& token : tokens) {
        std::cout << "Token Type: " << static_cast<int>(token.type) << std::endl;
    }
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