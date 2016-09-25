#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>

// type declarations
typedef uint8_t byte;
typedef std::vector<std::string> strings;

enum State : byte {
    START,
    READCHAR,
    READBLOCK,
    SKIP,
    DUMP,
    COMMENT,
    END
};

class Lexer {
    bool st_isspace(char c);
    bool st_isspecial(char c);
    bool st_isgroup(char c);
    char end_char, beg_char;

    public:
    strings lex(std::string s);
};

#endif // LEXER_H
