g++ -std=c++17 -o ./build/main ./src/main.cpp ./src/parsing.cpp ./src/statementize.cpp ./src/generation.cpp
cd ./build
./main
nasm -f macho64 ./out.asm
ld ./out.o -o ../out -macosx_version_min 10.15.7 -lSystem
cd ../
./out