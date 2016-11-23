#include "punctuator.h"

#include <stdlib.h>
#include "reg_exp.h"



lexeme *find_punctuator(char *seq)
{
    int n = 48;
    static char* keys[] = {
        "[", "]", "(", ")", "{", "}", ".", "->",
        "++", "--", "&", "*", "+", "-", "~", "!",
        "/", "%", "<<", ">>", "<", ">", "<=", ">=",
        "==", "!=", "^", "|", "&&", "||", "?", ":",
        ";", "...", "=", "*=", "/=", "%=", "+=", "-=",
        "<<=", ">>=", "&=", "^=", "|=", ",", "#", "##"
    };

    return reg_exp_compare(seq, PUNCTUATOR, keys, n);
}
