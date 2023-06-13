#ifndef CPU_HPP
#define CPU_HPP

#include <array>
#include <vector>
#include <stack>
#include "DataStructures.hpp"

class CPU {
private:
    std::stack<int32_t> stack;
    const std::vector<int32_t> program;
    bool running = true;
    std::array<int32_t, Registers::NUM_OF_REGISTERS> registers;
    bool is_jmp = false;
public:
    CPU(std::vector<int32_t> program_data);

    int32_t fetch();

    void eval(int32_t instr);

    void run();

    [[maybe_unused]] bool reset();
};


#endif
