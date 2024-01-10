//
// This is the main file that controls everything
//

#include "generation.hpp"

int main() {
    std::string line; // a buffer for looping through line by line
    std::string content; // the string that will be sent of into the parser
    std::ifstream file("input.ds"); // opens the input file
    if (file.is_open()) { // if file opened succesfully
        while (getline(file, line)) {
            if(line[0] != '#') // get the comments out straight away
            {
                content += line; // add line to the string
            }
        }
        file.close(); // close the file
    }
    else {
        std::perror("input file error"); // good practice
    }
    CodeParser parser; // create instance
    std::vector<Token> parsed = parser.parse(&content, content.size()); // parse
    CodeStatementizer statementizer; // create instance
    std::vector<Statement> statementized = statementizer.statementize(parsed); // statementize
    CodeGenerator generator; // create instance
    generator.generate(statementized); // generate
    return 0;
}

