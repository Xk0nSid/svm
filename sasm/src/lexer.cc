#include "lexer.h"

strings Lexer::lex(std::string s) {
    strings strlst;
    char lexeme[256];
    int i = 0, j = 0;
    State state = START;
    // int done = 0;
    int len = s.length();
    int balance = 0;

    while(i < len) {
        switch(state) {
            case START:
                if (st_isspace(s[i])) {
                    state = SKIP;
                } else if (st_isgroup(s[i])) {
                    if (s[i] == '"') {
                        lexeme[j] = s[i];
                        j++;
                        i++;
                    }
                    state = READBLOCK;
                } else if (s[i] == '/' && s[i+1] == '/') {
                    i += 2;
                    state = COMMENT;
                } else {
                    state = READCHAR;
                }
                break;
            case READCHAR:
                if (st_isspace(s[i])) {
                    state = DUMP;
                } else if (s[i] == '\\') {
                    i += 2;
                } else if (st_isgroup(s[i])) {
                    if (s[i] == '"') {
                        lexeme[j] = s[i];
                        j++;
                        i++;
                    }
                    state = READBLOCK;
                } else if (st_isspecial(s[i])) {
                    if (j == 0) {
                        lexeme[j] = s[i];
                        j++;
                        i++;
                    }
                    state = DUMP;
                } else if (s[i] == '/' && s[i+1] == '/') {
                    i += 2;
                    state = COMMENT;
                } else {
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                break;
            case READBLOCK:
                if (s[i] == beg_char && s[i] != '"') {
                    balance++;
                    lexeme[j] = s[i];
                    j++;
                    i++;
                } else if (s[i] == end_char) {
                    balance--;
                    lexeme[j] = s[i];
                    j++;
                    i++;
                    if (balance <= 0) {
                        state = DUMP;
                    }
                } else if (end_char == '"' && s[i] == '\\') {
                    // TODO: Fix this to actually record the chars
                    i += 2;
                } else {
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                break;
            case SKIP:
                if (st_isspace(s[i])) {
                    i++;
                } else {
                    state = READCHAR;
                }
                break;
            case DUMP:
                if (j > 0) {
                    lexeme[j] = 0;
                    strlst.push_back(lexeme);
                    j = 0;
                }
                state = START;
                #if DEBUG == 1
                if(debug) {
                  std::cout << "Token: " << lexeme << std::endl;
                }
                #endif
                break;
            case COMMENT:
                if (s[i] != '\n') {
                    i++;
                } else {
                    state = READCHAR;
                }
                break;
            case END:
                i = len;
                break;
        }
    }

    if (j > 0) {
        lexeme[j] = 0;
        strlst.push_back(lexeme);
    }

    return strlst;
}

/*
 * This allows us to define what a space is.
 */
bool Lexer::st_isspace(char c) {
    switch(c) {
        case '\n':
        case '\r':
        case '\t':
        case ' ':
        case '\v':
        case '\f':
            return true;
        default:
            return false;
    }
}

bool Lexer::st_isgroup(char c) {
    this->beg_char = c;
    switch(c) {
        case '"':
            this->end_char = '"';
            return true;
        case '(':
            this->end_char = ')';
            return true;
        case ')':
            return true;
        default:
            return false;
    }
}

bool Lexer::st_isspecial(char c) {
    switch(c) {
        case '[':
        case ']':
            return true;
        default:
            return false;
    }
}
