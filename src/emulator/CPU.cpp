#include <iostream>
#include "CPU.hpp"

//TODO logging

[[maybe_unused]] CPU::CPU(std::vector<int32_t> program_data) : program(program_data), registers() {
    registers.fill(0);
}

int32_t CPU::fetch() {
    int32_t value;
    try {
        value = program.at(registers[Registers::IP]);
    }
    catch (std::out_of_range &e) {
        value = InstructionSet::HLT;
        std::cout << "Access outside of program memory giving HALT";
        running = false;
    }
    return value;
}

void CPU::eval(int32_t instr) {
    is_jmp = false;
    switch (instr) {
        case InstructionSet::HLT: {
            running = false;
            std::cout << "Halt Received Terminating" << "\n";
            break;
        }
        case InstructionSet::PSH: {
            stack.push(program[++registers[Registers::IP]]);
            break;
        }
        case InstructionSet::POP: {
            if (stack.empty()) {
                running = false;
                std::cout << "cannot pop empty stack Terminating" << "\n";
            } else {
                int32_t value = stack.top();
                stack.pop();
                std::cout << "Popped Value is: " << value << "\n";
            }
            break;
        }
        case InstructionSet::ADD: {
            if (stack.size() < 2) {
                running = false;
                std::cout << "cannot add not enough numbers Terminating" << "\n";
            } else {
                registers[Registers::A] = stack.top();
                stack.pop();
                registers[Registers::B] = stack.top();
                stack.pop();
                registers[Registers::C] = registers[Registers::A] + registers[Registers::B];
                stack.push(registers[Registers::C]);
            }
            break;
        }
        case InstructionSet::MUL: {
            if (stack.size() < 2) {
                running = false;
                std::cout << "cannot multiply not enough numbers Terminating" << "\n";
            } else {
                registers[Registers::A] = stack.top();
                stack.pop();
                registers[Registers::B] = stack.top();
                stack.pop();
                registers[Registers::C] = registers[Registers::A] * registers[Registers::B];
                stack.push(registers[Registers::C]);
            }
            break;
        }
        case InstructionSet::DIV: {
            if (stack.size() < 2) {
                running = false;
                std::cout << "cannot multiply not enough numbers Terminating" << "\n";
            } else {
                registers[Registers::A] = stack.top();
                stack.pop();
                registers[Registers::B] = stack.top();
                stack.pop();
                registers[Registers::C] = floor(registers[Registers::A] / registers[Registers::B]);
                stack.push(registers[Registers::C]);
            }
            break;
        }
        case InstructionSet::SUB: {
            if (stack.size() < 2) {
                running = false;
                std::cout << "cannot subtract not enough numbers Terminating" << "\n";
            } else {
                registers[Registers::A] = stack.top();
                stack.pop();
                registers[Registers::B] = stack.top();
                stack.pop();
                registers[Registers::C] = registers[Registers::A] - registers[Registers::B];
                stack.push(registers[Registers::C]);
            }
            break;
        }
        case InstructionSet::SET: {
            registers[program[registers[Registers::IP] + 1]] = program[registers[
                    Registers::IP + 2]];
            registers[Registers::IP] += 2;
            break;
        }
        case InstructionSet::IFF: {
            if (registers[Registers::C] == program[registers[Registers::IP] + 1]) {
                registers[Registers::IP] = program[registers[Registers::IP] + 2];
                is_jmp = true;
            } else {
                registers[Registers::IP] += 2;
            }
            break;
        }
        case InstructionSet::IFN: {
            if (registers[Registers::C] != program[registers[Registers::IP] + 1]) {
                registers[Registers::IP] = program[registers[Registers::IP] + 2];
                is_jmp = true;
            } else {
                registers[Registers::IP] += 2;
            }
            break;
        }
        case InstructionSet::STR: {
            if (!stack.empty()) {
                int32_t value = stack.top();
                stack.pop();
                registers[program[registers[Registers::IP] + 1]] = value;
                registers[Registers::IP]++;
            } else {
                running = false;
                std::cout << "cannot pop empty stack Terminating" << "\n";
            }
            break;
        }
        case InstructionSet::RTS: {
            int32_t value = registers[program[registers[Registers::IP] + 1]];
            registers[Registers::IP]++;
            stack.push(value);
            break;
        }
        case InstructionSet::NOP: {
            std::cout << "NOP" << "\n";
            break;
        }
        case InstructionSet::MOV: {
            registers[program[registers[Registers::IP] + 1]] = registers[program[registers[Registers::IP] + 2]];
            registers[Registers::IP] += 2;
            break;
        }
        case InstructionSet::OUT: {
            int32_t io_register = program[registers[Registers::IP] + 1];
            if (!stack.empty()) {
                int32_t value = stack.top();
                stack.pop();
                switch (io_register) {
                    case (Registers::IO): {
                        std::cout << value << "\n";
                    }
                    default: {
                        registers[io_register] = value;
                    }
                }
            } else {
                running = false;
                std::cout << "cannot pop empty stack Terminating" << "\n";
            }
            registers[Registers::IP]++;
            break;
        }
        default: {
            running = false;
            std::cout << "unknown instruction Terminating" << "\n";
            break;
        }
    }
}

void CPU::run() {
    while (running) {
        eval(fetch());
        if (!is_jmp) {
            registers[Registers::IP]++;
        }
    }
}

[[maybe_unused]] bool CPU::reset() {
    if (!running) {
        registers.fill(0);
        while (!stack.empty()) {
            stack.pop();
        }
        return true;
    } else {
        return false;
    }
}
