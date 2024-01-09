#include <iostream>
#include <fstream>
#include <string>

void generate(std::string* asmcode);

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
    std::cout << content;
    generate(&content);
    return 0;
}
void generate(std::string* asmcode)
{
 std::ofstream outputFile("out.asm");

    // Check if the file is successfully opened
    if (outputFile.is_open()) {
        // Write some content to the file
        outputFile << *asmcode;

        // Close the file
        outputFile.close();

        std::cout << "Generated.\n";
    } else {
        std::cerr << "Unable to open the file.\n";
    }
    return;
}