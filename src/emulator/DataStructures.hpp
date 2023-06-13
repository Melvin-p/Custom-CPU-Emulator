#ifndef DATASTRUCTURES_HPP
#define DATASTRUCTURES_HPP

typedef enum {
    PSH, //Push number on to stack | 0x0 0xFF
    ADD, //Pop two values from the stack a b, then a+b, store result in register C and push on to stack | 0x1
    POP, //pop a number from the stack, value destroyed | 0x2
    SET, //set a registers value | 0x3 0x55 0x21
    HLT, //Halt stop execution | 0x4
    MUL, //Pop two values from the stack a b, then a*b, store result in register C and push on to stack | 0x5
    DIV, //Pop two values from the stack a b, then floor(a/b), store result in register C and push on to stack | 0x6
    SUB, //Pop two values from the stack a b, then a-b, store result in register C and push on to stack | 0x7
    RTS, //Register to stack, push value from register to stack | 0x8 0x3
    STR, //Stack to register pop value from stack push to register | 0x9 0x3
    NOP, //No operation | 0xA
    IFF, //checks if value in accumulator is equal to input value if so jumps | 0xB 0x3 0x2
    IFN, //checks if value in accumulator is not equal to input value if so jumps  | 0xc 0x3 0x2
    MOV, //Moves value copies value from first register to second | 0xD 0x2 0x3
    OUT, //Pop stack and write to IO register | 0xE 0x6
    IFL, //checks if value in accumulator is less than the input value if so jumps | 0xF 0x3 0x2
    IFG, //checks if value in accumulator is greater than the input value if so jumps | 0x10 0x3 0x2
} InstructionSet;

typedef enum {
    IP, //Instruction Pointer
    A,  //General Purpose but l-value is stored here
    B,  //General Purpose but r-value is store here
    C,  //General Purpose but can be considered accumulator
    D [[maybe_unused]],  //General Purpose
    E [[maybe_unused]],  //General Purpose
    IO, //IO writes character to the terminal
    NUM_OF_REGISTERS
} Registers;

#endif //DATASTRUCTURES_HPP
