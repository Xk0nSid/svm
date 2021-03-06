#include <iostream>
#include <fstream>
#include "lexer.h"

typedef uint32_t i32;

using namespace std;

vector<i32> compileToInstructions(strings s);
bool isInteger(string s);
bool isPrimitive(string s);
i32 mapToNumber(string s);

int main(int argc, char *argv[]) {
    // check for input errors
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        exit(1);
    }

    // read the input file
    ifstream infile;
    infile.open(argv[1]);
    if (!infile.is_open()) {
        cout << "Failed to open file " << argv[1] << endl;
        exit(1);
    }
    string line;
    string contents;
    while (getline(infile, line)) {
        contents += line + "\n";
    }
    infile.close();

    // parse the file
    Lexer lexer;
    strings lexemes = lexer.lex(contents);

    // compiler to binary
    vector<i32> instructions = compileToInstructions(lexemes);

    // write to binary file
    ofstream ofile;
    ofile.open("a.sbc", ios::binary);
    
    for (i32 i = 0; i < instructions.size(); i++) {
        ofile.write(reinterpret_cast<char *>(&instructions[i]), sizeof(i32));
    }
    return 0;
}

vector<i32> compileToInstructions(strings s) {
    vector<i32> instructions;
    for (i32 i = 0; i < s.size(); i++) {
        if (isInteger(s[i])) {
            instructions.push_back(stoi(s[i]));
        } else {
            i32 instruction = mapToNumber(s[i]);
            if (instruction != -1) {
                instructions.push_back(instruction);
            } else {
                cout << "Invalid instruction: " << s[i] << endl;
                exit(1);
            }
        }
    }
    // Add halt instruction at the end
    instructions.push_back(0x40000000);
    return instructions;
}

bool isInteger(string s) {
    for (i32 i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

i32 mapToNumber(string s) {
    if (s == "hlt") {
        return 0x40000000;
    } else if (s == "+" || s == "add") {
        return 0x40000001;
    } else if (s == "-" || s == "sub") {
        return 0x40000002;
    } else if (s == "*" || s == "mul") {
        return 0x40000003;
    } else if (s == "/" || s == "div") {
        return 0x40000004;
    } else if (s == "push") {
        return 0x40000005;
    } else if (s == "print") {
        return 0x40000006;
    }
    return -1;
}
