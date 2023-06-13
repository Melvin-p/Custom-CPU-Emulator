#include "CPU.hpp"

int main() {

    //TODO read program from file

    std::vector<int32_t> buffer = {
            PSH, 5,
            PSH, 6,
            ADD,
            PSH, 2,
            MUL,
            IF, Registers::C, 22, 2,
            RTS, Registers::C,
            STR, Registers::C,
            OUT, Registers::IO,
            NOP,
            HLT
    };

    CPU cpu(buffer);

    cpu.run();

}