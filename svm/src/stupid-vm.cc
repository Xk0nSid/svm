#include "stupid-vm.h"
#include "svmmeta.h"

/*
 * Instruction format
 * header: 2 bits
 * data: 30 bits
 *
 * header format:
 * 0 => positive integer
 * 1 => primitive instruction
 * 2 => negative integer
 * 3 => undefined
 *
 */

void StackVM::displayMeta() {
    std::cout << "Stupid Virtual Machine " << _SVM_VERSION_ << " (SVM)" << std::endl
              << _SVM_COMPILER_ << " " << _SVM_COMPILER_VERSION_ << " on "
              << _SVM_ARCH_ << " linux." << std::endl
              << "Instruction Set: Primitive" << std::endl
              << "Set Length: 7" << std::endl
              << "Instruction Size: 32 bit" << std::endl
              << std::endl;
}

StackVM::StackVM() {
    this->memory.reserve(1000000);
}

i32 StackVM::getType(i32 instruction) {
    i32 type = 0xc0000000;
    type = (type & instruction) >> 30;
    return type;
}

i32 StackVM::getData(i32 instruction) {
    i32 data = 0x3fffffff;
    data = data & instruction;
    return data;
}

void StackVM::fetch() {
    this->pc++;
}

void StackVM::decode() {
    this->typ = this->getType(this->memory[this->pc]);
    this->dat = this->getData(this->memory[this->pc]);
}

void StackVM::execute() {
    if (this->typ == 0 || typ == 2) {
        this->sp++;
        this->memory[this->sp] = dat;
    } else {
        doPrimitive();
    }
}

void StackVM::doPrimitive() {
    switch(this->dat) {
        case 0:     // Halt
            #if DEBUG == 1
            std::cout << "Halting VM..." << std::endl;
            #endif
            this->running = 0;
            break;
        case 1:     // Add
            #if DEBUG == 1
            std::cout << "adding " << this->memory[this->sp -1]
                      << " " << this->memory[this->sp] << std::endl;
            #endif
            memory[this->sp -1] = this->memory[this->sp -1] + this->memory[this->sp];
            this->sp--;
            break;
        case 2:     // Subtract
            #if DEBUG == 1
            std::cout << "subtracting " << this->memory[this->sp -1]
                      << " " << this->memory[this->sp] << std::endl;
            #endif
            memory[this->sp -1] = this->memory[this->sp -1] - this->memory[this->sp];
            this->sp--;
            break;
        case 3:     // Multiply
            #if DEBUG == 1
            std::cout << "multiply " << this->memory[this->sp -1]
                      << " " << this->memory[this->sp] << std::endl;
            #endif
            memory[this->sp -1] = this->memory[this->sp -1] * this->memory[this->sp];
            this->sp--;
            break;
        case 4:     // Divide
            #if DEBUG == 1
            std::cout << "divide " << this->memory[this->sp -1]
                      << " " << this->memory[this->sp] << std::endl;
            #endif
            memory[this->sp -1] = this->memory[this->sp -1] / this->memory[this->sp];
            this->sp--;
            break;
        case 5:     // Push
            break;
        case 6:     // Print
            std::cout << this->memory[this->sp] << std::endl;
            break;
    }
}

void StackVM::run() {
    this->displayMeta();
    this->pc -= 1;
    while (this->running == 1) {
        this->fetch();
        this->decode();
        this->execute();
        #if DEBUG == 1
        std::cout << "tos: " << this->memory[this->sp] << std::endl;
        #endif
    }
}

void StackVM::loadProgram(std::vector<i32> prog) {
    for (i32 i = 0; i < prog.size(); i++) {
        this->memory[this->pc + i] = prog[i];
    }
}
