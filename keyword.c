#include "keyword.h"

#include <stdlib.h>
#include "reg_exp.h"



lexeme *find_keyword(char *seq)
{
    int n = 37;
    static char* keywords[] = {
      "auto", "break", "case", "char",
      "const", "continue", "default", "do",
      "double", "else", "enum", "extern",
      "float", "for", "goto", "if",
      "inline", "int", "long", "register",
      "restrict", "return", "short", "signed",
      "sizeof", "static", "struct", "switch",
      "typedef", "union", "unsigned", "void",
      "volatile", "while", "_Bool", "_Complex", "_Imaginary"
    };

    return reg_exp_compare(seq, KEYWORD, keywords, n);
}
