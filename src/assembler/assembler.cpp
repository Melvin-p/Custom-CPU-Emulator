#include "assembler.hpp"
#include <array>
#include <iostream>
#include <vector>

#include "../emulator/DataStructures.hpp"


namespace tokens {
    constexpr std::array<char, 4> PSH{'P', 'S', 'H', 1};
    constexpr std::array<char, 4> ADD{'A', 'D', 'D', 0};
    constexpr std::array<char, 4> POP{'P', 'O', 'P', 0};
    constexpr std::array<char, 4> SET{'S', 'E', 'T', 2};
    constexpr std::array<char, 4> HLT{'H', 'L', 'T', 0};
    constexpr std::array<char, 4> MUL{'M', 'U', 'L', 0};
    constexpr std::array<char, 4> DIV{'D', 'I', 'V', 0};
    constexpr std::array<char, 4> SUB{'S', 'U', 'B', 0};
    constexpr std::array<char, 4> RTS{'R', 'T', 'S', 1};
    constexpr std::array<char, 4> STR{'S', 'T', 'R', 1};
    constexpr std::array<char, 4> NOP{'N', 'O', 'P', 0};
    constexpr std::array<char, 4> IFF{'I', 'F', 'F', 2};
    constexpr std::array<char, 4> IFN{'I', 'F', 'N', 2};
    constexpr std::array<char, 4> MOV{'M', 'O', 'V', 2};
    constexpr std::array<char, 4> OUT{'O', 'U', 'T', 1};
}

uint64_t get_current_line(std::ifstream &file) {
    auto original_pos = file.tellg();
    uint64_t line_count = 1;
    file.seekg(0);
    char c;
    while ((file.tellg() < original_pos) && file.get(c)) {
        if (c == '\n') {
            line_count++;
        }
    }
    return line_count;
}

void skip_whitespace(std::ifstream &file) {
    while (!file.eof()) {
        auto c = file.peek();
        if (isspace(c)) {
            file.get();
        } else {
            break;
        }
    }
}

int32_t read_digit(std::ifstream &file) {
    std::string s;
    int value = 0;
    while (!file.eof()) {
        int c = file.get();
        if (isdigit(c) || c == '-') {
            s.push_back(static_cast<char>(c));
        } else {
            file.unget();
            try {
                value = std::stoi(s);
            }
            catch (std::invalid_argument &e) {
                auto line_no = get_current_line(file);
                std::cerr << "Bad Number at: " << line_no << "\n";
                file.close();
                exit(1);
            }
            catch (std::out_of_range &e) {
                auto line_no = get_current_line(file);
                std::cerr << "Number to large at: " << line_no << "\n";
                file.close();
                exit(1);
            }
            break;
        }
    }
    return value;
}

void generate(std::ifstream &file, const std::string &filename) {
    std::vector<int32_t> out;
    std::array<char, 3> buffer{};
    skip_whitespace(file);
    while (file.read(buffer.data(), buffer.size())) {
        if (std::equal(buffer.begin(), buffer.end(), tokens::PSH.begin(), tokens::PSH.end() - 1)) {
            std::cout << "PSH ";
            out.push_back(InstructionSet::PSH);
            skip_whitespace(file);
            for (int i = 0; i < tokens::PSH[3]; ++i) {
                out.push_back(read_digit(file));
                skip_whitespace(file);
            }
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::ADD.begin(), tokens::ADD.end() - 1)) {
            std::cout << "ADD";
            out.push_back(InstructionSet::ADD);
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::IFF.begin(), tokens::IFF.end() - 1)) {
            std::cout << "IFF ";
            out.push_back(InstructionSet::IFF);
            skip_whitespace(file);
            for (int i = 0; i < tokens::IFF[3]; ++i) {
                out.push_back(read_digit(file));
                skip_whitespace(file);
            }
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::IFN.begin(), tokens::IFN.end() - 1)) {
            std::cout << "IFN ";
            out.push_back(InstructionSet::IFN);
            skip_whitespace(file);
            for (int i = 0; i < tokens::IFN[3]; ++i) {
                out.push_back(read_digit(file));
                skip_whitespace(file);
            }
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::POP.begin(), tokens::POP.end() - 1)) {
            std::cout << "POP";
            out.push_back(InstructionSet::POP);
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::SET.begin(), tokens::SET.end() - 1)) {
            std::cout << "SET ";
            out.push_back(InstructionSet::SET);
            skip_whitespace(file);
            for (int i = 0; i < tokens::SET[3]; ++i) {
                out.push_back(read_digit(file));
                skip_whitespace(file);
            }
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::HLT.begin(), tokens::HLT.end() - 1)) {
            std::cout << "HLT";
            out.push_back(InstructionSet::HLT);
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::MUL.begin(), tokens::MUL.end() - 1)) {
            std::cout << "MUL";
            out.push_back(InstructionSet::MUL);
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::DIV.begin(), tokens::DIV.end() - 1)) {
            std::cout << "DIV";
            out.push_back(InstructionSet::DIV);
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::SUB.begin(), tokens::SUB.end() - 1)) {
            std::cout << "SUB";
            out.push_back(InstructionSet::SUB);
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::RTS.begin(), tokens::RTS.end() - 1)) {
            std::cout << "RTS ";
            out.push_back(InstructionSet::RTS);
            skip_whitespace(file);
            for (int i = 0; i < tokens::RTS[3]; ++i) {
                out.push_back(read_digit(file));
                skip_whitespace(file);
            }
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::STR.begin(), tokens::STR.end() - 1)) {
            std::cout << "STR ";
            out.push_back(InstructionSet::STR);
            skip_whitespace(file);
            for (int i = 0; i < tokens::STR[3]; ++i) {
                out.push_back(read_digit(file));
                skip_whitespace(file);
            }
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::NOP.begin(), tokens::NOP.end() - 1)) {
            std::cout << "NOP";
            out.push_back(InstructionSet::NOP);
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::MOV.begin(), tokens::MOV.end() - 1)) {
            std::cout << "MOV ";
            out.push_back(InstructionSet::MOV);
            skip_whitespace(file);
            for (int i = 0; i < tokens::MOV[3]; ++i) {
                out.push_back(read_digit(file));
                skip_whitespace(file);
            }
            std::cout << "\n";
            skip_whitespace(file);
        } else if (std::equal(buffer.begin(), buffer.end(), tokens::OUT.begin(), tokens::OUT.end() - 1)) {
            std::cout << "OUT ";
            out.push_back(InstructionSet::OUT);
            skip_whitespace(file);
            for (int i = 0; i < tokens::OUT[3]; ++i) {
                out.push_back(read_digit(file));
                skip_whitespace(file);
            }
            std::cout << "\n";
            skip_whitespace(file);
        } else {
            std::cerr << "Unknown instruction at: ";
            std::cerr << get_current_line(file);
            file.close();
            exit(1);
        }
        std::ofstream outfile(filename, std::ios::out | std::ios::binary);
        constexpr int32_t size = 0;
        if (outfile.is_open()) {
            for (const int32_t i: out) {
                outfile.write((char *) &i, sizeof(size));
            }
        } else {
            std::cerr << "Failed to write to file" << "\n";
        }
        outfile.close();
    }

}