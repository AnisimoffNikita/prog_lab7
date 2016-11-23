#ifndef REG_EXP_H
#define REG_EXP_H

#include "types.h"

typedef enum
{
    INITIAL,
    STATE_0,
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
    STATE_5,
    STATE_6,
    STATE_7,
    STATE_8,
    STATE_9,
    FAIL,
} state;

typedef int (*get_signal_func)(char);

lexeme *find_lexeme(char *seq, get_signal_func get_signal, state** transitions);

#endif // REG_EXP_H
