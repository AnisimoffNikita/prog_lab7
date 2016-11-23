#include "constant_float.h"
#include <ctype.h>
#include <stdlib.h>

#include "reg_exp.h"

typedef enum
{
    DIGIT,
    DOT,
    E,
    SIGN,
    OTHER
} signal;


lexeme *find_float_constant(char *seq);
lexeme *find_scientific_constant(char *seq);

lexeme *find_floating_constant(char *seq)
{
    lexeme *a[2];
    a[0] = find_float_constant(seq);
    a[1] = find_scientific_constant(seq);
    return get_longest(a, 2);
}


lexeme *find_float_constant(char *seq)
{
    int get_signal(char a)
    {
        if (a == '.')
            return DOT;
        else if (isdigit(a))
            return DIGIT;
        else
            return OTHER;
    }
    static state transitions[MAX_STATES][MAX_SIGNALS] = {
        [STATE_0][OTHER] = STATE_9,
        [STATE_0][DIGIT] = STATE_1,
        [STATE_0][DOT] = STATE_2,
        [STATE_1][OTHER] = STATE_9,
        [STATE_1][DIGIT] = STATE_9,
        [STATE_1][DOT] = STATE_2,
        [STATE_2][OTHER] = STATE_9,
        [STATE_2][DIGIT] = STATE_1,
        [STATE_2][DOT] = STATE_9,
    };

    static state finals[2] = {STATE_1, STATE_2};

    return reg_exp(seq, get_signal, transitions, FLOAT_CONSTANT, finals, 2);
}

lexeme *find_scientific_constant(char *seq)
{
    int get_signal(char a)
    {
        if (a == '.')
            return DOT;
        else if (isdigit(a))
            return DIGIT;
        else if (a == 'E' || a == 'e')
            return E;
        else if (a == '+' || a == '-')
            return SIGN;
        else
            return OTHER;
    }
    static state transitions[MAX_STATES][MAX_SIGNALS] = {
        [STATE_0][OTHER] = STATE_9,
        [STATE_0][DIGIT] = STATE_0,
        [STATE_0][DOT] = STATE_1,
        [STATE_0][E] = STATE_3,
        [STATE_0][SIGN] = STATE_9,

        [STATE_1][OTHER] = STATE_9,
        [STATE_1][DIGIT] = STATE_2,
        [STATE_1][DOT] = STATE_9,
        [STATE_1][E] = STATE_3,
        [STATE_1][SIGN] = STATE_9,

        [STATE_2][OTHER] = STATE_9,
        [STATE_2][DIGIT] = STATE_2,
        [STATE_2][DOT] = STATE_9,
        [STATE_2][E] = STATE_3,
        [STATE_2][SIGN] = STATE_9,

        [STATE_3][OTHER] = STATE_9,
        [STATE_3][DIGIT] = STATE_5,
        [STATE_3][DOT] = STATE_9,
        [STATE_3][E] = STATE_9,
        [STATE_3][SIGN] = STATE_4,

        [STATE_4][OTHER] = STATE_9,
        [STATE_4][DIGIT] = STATE_4,
        [STATE_4][DOT] = STATE_9,
        [STATE_4][E] = STATE_9,
        [STATE_4][SIGN] = STATE_9,
    };

    static state finals[1] = {STATE_4};

    return reg_exp(seq, get_signal, transitions, FLOAT_CONSTANT, finals, 1);
}
