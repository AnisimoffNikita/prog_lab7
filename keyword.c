#include "keyword.h"

#include <stdlib.h>

enum _signal
{
    OK,
    OTHER
};
typedef enum _signal signal;

enum _state
{
    INITIAL,
    FINISH,
    FAIL
};
typedef enum _state state;

#define SIZE 37

static char* str_equal(char *a, char *b)
{
    char *s = b;
    while (a && b)
    {
        if (*a != *b)
            return NULL;
        a++;
        b++;
    }
    return s;
}

static signal get_signal(char *w, char **end)
{
    static char* keywords[SIZE] = {
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
    for (int i = 0; i < SIZE; i++)
    {
        *end = str_equal(w, keywords[i]);
        if (*end)
            return OK;
    }

    return OTHER;
}

lexeme *find_keyword(char *seq)
{
    static state transitions[3][2] = {
        [INITIAL][OK] = FINISH,
        [INITIAL][OTHER] = FAIL
    };

    state st = INITIAL;

    char* end;
    signal sg = get_signal(seq, &end);
    st = transitions[st][sg];

    lexeme *l = create_lexeme(end, KEYWORD);
    if (st == FINISH)
        return l;
    else
        return NULL;
}
