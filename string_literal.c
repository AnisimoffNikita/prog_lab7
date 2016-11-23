#include "string_literal.h"

#include <ctype.h>
#include <stdlib.h>

#include "reg_exp.h"

typedef enum
{
    QUOTE,
    CHAR,
    BACKSLASH,
    ESCAPE,
    OTHER
} signal;

static int is_escape(char a)
{
    return a == '\'' ||
            a == '\"' ||
            a == '\?' ||
            a == '\\' ||
            a == '\a' ||
            a == '\b' ||
            a == '\f' ||
            a == '\n' ||
            a == '\r' ||
            a == '\t' ||
            a == '\v';
}

static int get_signal(char a)
{
    if (a == '\\')
        return BACKSLASH;
    else if (a == '\"')
        return QUOTE;
    else if (is_escape(a))
        return ESCAPE;
    else if (isprint(a))
        return CHAR;
    else
        return OTHER;
}

lexeme *find_string_literal(char *seq)
{
    static state transitions[MAX_STATES][MAX_SIGNALS] = {
        [STATE_0][OTHER] = STATE_9,
        [STATE_0][CHAR] = STATE_9,
        [STATE_0][BACKSLASH] = STATE_9,
        [STATE_0][ESCAPE] = STATE_9,
        [STATE_0][QUOTE] = STATE_1,

        [STATE_1][OTHER] = STATE_9,
        [STATE_1][CHAR] = STATE_1,
        [STATE_1][BACKSLASH] = STATE_2,
        [STATE_1][ESCAPE] = STATE_1,
        [STATE_1][QUOTE] = STATE_3,

        [STATE_2][OTHER] = STATE_9,
        [STATE_2][CHAR] = STATE_9,
        [STATE_2][BACKSLASH] = STATE_1,
        [STATE_2][ESCAPE] = STATE_1,
        [STATE_2][QUOTE] = STATE_1,

        [STATE_3][OTHER] = STATE_9,
        [STATE_3][CHAR] = STATE_9,
        [STATE_3][BACKSLASH] = STATE_9,
        [STATE_3][ESCAPE] = STATE_9,
        [STATE_3][QUOTE] = STATE_9,
    };

    static state finals[1] = {STATE_3};

    return reg_exp(seq, get_signal, transitions, INT_CONSTANT, finals, 1);
}
