#include <iostream>
#include <fstream>
#include <string>

void generate(std::string* asmcode);
std::string template_read(const std::string& filename);

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
    generate(&content);
    return 0;
}

void generate(std::string* asmcode)
{
    std::string buf;
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