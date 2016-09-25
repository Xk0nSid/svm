#ifndef STACK_VM_H
#define STACK_VM_H

#include <iostream>
#include <vector>

// type definitions
typedef int32_t i32;

class StackVM {
    i32 pc = 100;               // Program Counter
    i32 sp = 0;                 // Stack Pointer
    std::vector<i32> memory;    // vm memory
    i32 typ = 0;                // type of current ins
    i32 dat = 0;                // data of current ins
    i32 running = 1;

    // Private Functions
    i32 getType(i32 instruction);
    i32 getData(i32 instruction);
    void fetch();
    void decode();
    void execute();
    void doPrimitive();

    public:
    StackVM();
    void run();
    void loadProgram(std::vector<i32> prog);
    void displayMeta();
};

#endif // STACK_VM_H
