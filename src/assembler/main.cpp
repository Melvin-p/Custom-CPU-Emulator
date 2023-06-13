#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include "assembler.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "no file provided" "\n";
        exit(1);
    } else {
        std::ifstream file(argv[1], std::ios::in);
        if (file.is_open()) {
            std::string s(argv[1]);
            auto dot = s.find_last_of('.');
            if (dot != std::string::npos) {
                s = s.substr(0, dot);
            }
            s += ".bin";
            generate(file, s);
            file.close();
        } else {
            std::cerr << "can't open file" << "\n";
            exit(1);
        }
    }
    return 0;
}
