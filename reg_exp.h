#ifndef REG_EXP_H
#define REG_EXP_H

#include "types.h"

#define MAX_SIGNALS 10
#define MAX_STATES 10

typedef enum
{
    STATE_0,
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
    STATE_5,
    STATE_6,
    STATE_7,
    STATE_8,
    STATE_9
} state;

typedef int (*get_signal_func)(char);

lexeme *get_longest(lexeme *l[], int n);

lexeme *reg_exp(char *seq, get_signal_func get_signal, state transitions[MAX_STATES][MAX_SIGNALS],
                    lexeme_type type, state *finals, int n);

#endif // REG_EXP_H
