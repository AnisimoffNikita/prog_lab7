#include "constant_int.h"

#include <ctype.h>
#include <stdlib.h>

#include "reg_exp.h"

typedef enum
{
    ZERO,
    DIGIT,
    X,
    OTHER
} signal;


lexeme *find_dec_constant(char *seq);
lexeme *find_oct_constant(char *seq);
lexeme *find_hex_constant(char *seq);

lexeme *find_int_constant(char *seq)
{
    lexeme *a[3];
    a[0] = find_dec_constant(seq);
    a[1] = find_oct_constant(seq);
    a[1] = find_hex_constant(seq);
    return get_longest(a, 3);
}
lexeme *find_dec_constant(char *seq)
{
    int get_signal(char a)
    {
        if (a == '0')
            return ZERO;
        else if (isdigit(a))
            return DIGIT;
        else
            return OTHER;
    }
    static state transitions[MAX_STATES][MAX_SIGNALS] = {
        [STATE_0][OTHER] = STATE_9,
        [STATE_0][ZERO] = STATE_9,
        [STATE_0][DIGIT] = STATE_1,
        [STATE_1][OTHER] = STATE_2,
        [STATE_1][ZERO] = STATE_1,
        [STATE_1][DIGIT] = STATE_1
    };

    static state finals[1] = {STATE_1};

    return reg_exp(seq, get_signal, transitions, INT_CONSTANT, finals, 1);
}

lexeme *find_oct_constant(char *seq)
{
    int get_signal(char a)
    {
        if (a == '0')
            return ZERO;
        else if (a >= '0' && a <= '7')
            return DIGIT;
        else
            return OTHER;
    }
    static state transitions[MAX_STATES][MAX_SIGNALS] = {
        [STATE_0][OTHER] = STATE_9,
        [STATE_0][ZERO] = STATE_1,
        [STATE_0][DIGIT] = STATE_9,
        [STATE_1][OTHER] = STATE_9,
        [STATE_1][ZERO] = STATE_1,
        [STATE_1][DIGIT] = STATE_1
    };

    static state finals[1] = {STATE_1};

    return reg_exp(seq, get_signal, transitions, INT_CONSTANT, finals, 1);
}

lexeme *find_hex_constant(char *seq)
{
    int get_signal(char a)
    {
        if (a == '0')
            return ZERO;
        else if (a == 'X' || a == 'x')
            return X;
        else if (isdigit(a) ||
                 (a > 'a' && a < 'f') ||
                 (a > 'A' && a < 'F'))
            return DIGIT;
        else
            return OTHER;
    }

    static state transitions[MAX_STATES][MAX_SIGNALS] = {
        [STATE_0][OTHER] = STATE_9,
        [STATE_0][ZERO] = STATE_1,
        [STATE_0][DIGIT] = STATE_9,
        [STATE_0][X] = STATE_9,
        [STATE_1][OTHER] = STATE_9,
        [STATE_1][ZERO] = STATE_9,
        [STATE_1][DIGIT] = STATE_9,
        [STATE_1][X] = STATE_2,
        [STATE_2][OTHER] = STATE_9,
        [STATE_2][ZERO] = STATE_2,
        [STATE_2][DIGIT] = STATE_2,
        [STATE_2][X] = STATE_9,
    };

    static state finals[1] = {STATE_2};

    return reg_exp(seq, get_signal, transitions, INT_CONSTANT, finals, 1);
}

