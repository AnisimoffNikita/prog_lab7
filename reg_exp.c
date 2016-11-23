#include "reg_exp.h"

#include <stdlib.h>

lexeme *get_longest(lexeme *l[], int n)
{
    lexeme *r = l[0];
    for (int i = 1; i < n; i++)
        if ((l != NULL && r == NULL) ||
            (l != NULL && r != NULL && l[i]->l > r->l))
            r = l[i];
    return r;
}

int is_final_state(state s, state *finals, int n)
{
    for (int i = 0; i < n; i++)
        if (s == finals[i])
            return 1;
    return 0;
}

lexeme *reg_exp(char *seq, get_signal_func get_signal, state transitions[MAX_STATES][MAX_SIGNALS], lexeme_type type, state *finals, int n)
{
    state st = STATE_0;
    state prev_st;
    int len = 0;
    char buf[LEXEME_SIZE];
    while (st != STATE_9)
    {
        int sg = get_signal(*seq);
        prev_st = st;
        st = transitions[st][sg];
        buf[len++] = *seq;
        seq++;
    }
    if (is_final_state(prev_st, finals, n))
    {
        buf[len] = 0;
        lexeme *l = create_lexeme(buf, type);
        return l;
    }
    else
        return NULL;
}

