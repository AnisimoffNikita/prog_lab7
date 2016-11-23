#include "reg_exp.h"

#include <stdlib.h>

lexeme *find_lexeme(char *seq, get_signal_func get_signal, state **transitions)
{
    state st = INITIAL;
    int len = 0;
    char buf[LEXEME_SIZE];
    while (st != FAIL)
    {
        int sg = get_signal(*seq);
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
