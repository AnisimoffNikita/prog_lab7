#include "int_constant.h"

#include <ctype.h>
#include <stdlib.h>

typedef enum
{
    ZERO,
    DIGIT,
    ALPHA,
    OTHER
} signal;

typedef enum
{
    INITIAL,
    X,
    FINAL,
    FAIL
} state;


lexeme *find_dec_constant(char *seq);
lexeme *find_oct_constant(char *seq);
lexeme *find_hex_constant(char *seq);

lexeme *find_int_constant(char *seq)
{

}

signal get_dec_signal(char a)
{
    if (a == '0')
        return ZERO;
    else if (isdigit(a))
        return DIGIT;
    else
        return OTHER;
}

lexeme *find_dec_constant(char *seq)
{
    static state transitions[3][4] = {
        [INITIAL][OTHER] = FAIL,
        [INITIAL][ZERO] = FAIL,
        [INITIAL][DIGIT] = FINAL,
        [FINAL][OTHER] = FAIL,
        [FINAL][ZERO] = FINAL,
        [FINAL][DIGIT] = FINAL,
    };

    state st = INITIAL;
    int len = 0;
    char buf[LEXEME_SIZE];
    while (st != FAIL)
    {
        signal sg = get_dec_signal(*seq);
        st = transitions[st][sg];
        buf[len++] = *seq;
        seq++;
    }

    if (len > 1)
    {
        buf[len] = 0;
        lexeme *l = create_lexeme(buf, IDENTIFIER);
        return l;
    }
    else
        return NULL;
}

lexeme *find_oct_constant(char *seq)
{
    static state transitions[3][4] = {
        [INITIAL][OTHER] = FAIL,
        [INITIAL][ZERO] = FINAL,
        [INITIAL][DIGIT] = FINAL,
        [FINAL][OTHER] = FAIL,
        [FINAL][ZERO] = FINAL,
        [FINAL][DIGIT] = FINAL,
    };

    state st = INITIAL;
    int len = 0;
    char buf[LEXEME_SIZE];
    while (st != FAIL)
    {
        signal sg = get_dec_signal(*seq);
        st = transitions[st][sg];
        buf[len++] = *seq;
        seq++;
    }

    if (len > 1)
    {
        buf[len] = 0;
        lexeme *l = create_lexeme(buf, IDENTIFIER);
        return l;
    }
    else
        return NULL;
}
