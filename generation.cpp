//
// this is the file that generates assembly code from the statements
//

#include "generation.hpp"

std::string sectiondata = "section .data\n"; // this is the data section for assembly
std::string sectiontext = "section .text\n\tglobal _main\n_main:\n"; // this is the text section and also this is where the main starts

void CodeGenerator::gen() // this is how it generates under the hood
{
    std::ofstream outputFile("out.asm"); // creating the output file

    // Check if the file is successfully opened
    if (outputFile.is_open()) { // if the file opened succesfully
        outputFile << sectiondata; // add the data section
        outputFile << sectiontext; // add the text section
        outputFile.close(); // close the file
    } else {
        std::cerr << "Unable to open the file.\n"; // error checking, good practice
    }
}

std::string genExit(std::string returnval) // this generates assembly version of exit
{
    std::string output = "\tmov rax, 0x02000001\n\tmov rdi, " + returnval + "\n\tsyscall\n";
    return output;
}

std::string genSTDOUT(std::string varname) // this generates assembly version of stdout
{
    std::string output = "\tmov rax, 0x02000004\n\tmov rdi, 1\n\tmov rsi, " + varname + "\n\tmov rdx, " + std::to_string(varname.size()) + "\n\tsyscall\n";
    return output;
}

std::string genVar(std::string val) // this generates the assembly version of a var
{
    std::string output = "\t" + val + ": db \""+ val +"\", 10\n";
    return output;
}

void CodeGenerator::generate(std::vector<Statement> statements) // this is the main method, which checks all the statements, and generates the asse,bly into the section variables
{
    for (int i = 0; i < statements.size(); i++) // looping through all the statements
    {
        if(statements[i].type == StatementType::_exit) // if it is an exit statement
        {
            if(statements[i].value.has_value()) // good practice
            {
                sectiontext += genExit(statements[i].value.value()); // add exit code assembly to section variable
            }
        }
        else if(statements[i].type == StatementType::_stdout) // if it is a stdout statement
        {
            if(statements[i].value.has_value()) // good practice
            {
                sectiondata += genVar(statements[i].value.value()); // store the value as a var in section variable
                sectiontext += genSTDOUT(statements[i].value.value()); // add stdout assembly code to section variable
            }
        }
    }
    gen(); // do stuff under the hood
}