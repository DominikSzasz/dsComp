g++ -std=c++17 -o main main.cpp parsing.cpp statementize.cpp generation.cpp
./main
nasm -f macho64 out.asm
ld out.o -o out -macosx_version_min 10.15.7 -lSystem
./out