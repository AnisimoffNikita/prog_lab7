#include "identifier.h"

#include <ctype.h>
#include <stdlib.h>

#include "reg_exp.h"

typedef enum
{
    DIGIT,
    ALPHA,
    _,
    OTHER
} signal;

static int get_signal(char a)
{
    if (isdigit(a))
        return DIGIT;
    else if (isalpha(a))
        return ALPHA;
    else if (a == '_')
        return _;
    else
        return OTHER;
}

lexeme *find_identifier(char *seq)
{
    static state transitions[MAX_STATES][MAX_SIGNALS] = {
        [STATE_0][OTHER] = STATE_9,
        [STATE_0][DIGIT] = STATE_9,
        [STATE_0][ALPHA] = STATE_1,
        [STATE_0][_] = STATE_1,
        [STATE_1][OTHER] = STATE_9,
        [STATE_1][DIGIT] = STATE_1,
        [STATE_1][ALPHA] = STATE_1,
        [STATE_1][_] = STATE_1
    };

    static state finals[1] = {STATE_1};

    return reg_exp(seq, get_signal, transitions, IDENTIFIER, finals, 1);
}
