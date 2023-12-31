#include "CPU.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    std::vector<int32_t> program;
    int32_t size = 0;
    if (argc < 2) {
        std::cerr << "no file provided" "\n";
        exit(1);
    } else {
        std::ifstream file(argv[1], std::ifstream::in | std::ifstream::binary);
        if (file.is_open()) {
            while (!file.eof()) {
                file.read((char *) &size, sizeof(size));
                program.push_back(size);
            }
            file.close();
        } else {
            std::cerr << "can't open file" << "\n";
            exit(1);
        }
    }

    CPU cpu(program);

    cpu.run();

}