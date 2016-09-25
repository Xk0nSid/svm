#include <fstream>
#include "stupid-vm.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename> " << std::endl;
        exit(1);
    }

    std::ifstream r(argv[1], std::ios::binary);
    i32 i;
    std::vector<i32> prog;

    while(r.read((char*)&i, sizeof(i))) {
        prog.push_back(i);
    }

    StackVM vm = StackVM();
    vm.loadProgram(prog);
    vm.run();
    return 0;
}
