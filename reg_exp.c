#include "reg_exp.h"

#include <stdlib.h>

lexeme *get_longest(lexeme *l[], int n)
{
    lexeme *r = l[0];
    for (int i = 1; i < n; i++)
        if ((l[i] != NULL && r == NULL) ||
            (l[i] != NULL && r != NULL && l[i]->l > r->l))
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
        buf[len-1] = 0;
        lexeme *l = create_lexeme(buf, type);
        return l;
    }
    else
        return NULL;
}


//да, можно было тупо перебрать все слова, но ведь через регулярки веселее :D
typedef enum
{
    OK,
    ERROR
} compare_signals;

static char* str_equal(char *a, char *b)
{
    char *s = b;
    while (*a && *b)
    {
        if (*a != *b)
            return NULL;
        a++;
        b++;
    }
    return s;
}

static int get_signal(char *w, char **buf, char **keys, int n)
{
    for (int i = 0; i < n; i++)
    {
        *buf = str_equal(w, keys[i]);
        if (*buf)
            return OK;
    }

    return ERROR;
}

lexeme *reg_exp_compare(char *seq, lexeme_type type, char **keys, int n)
{
    state st = STATE_0;

    static state transitions[MAX_STATES][MAX_SIGNALS] = {
        [STATE_0][OK] = STATE_1,
        [STATE_0][ERROR] = STATE_9
    };

    char* buf;
    int sg = get_signal(seq, &buf, keys, n);
    st = transitions[st][sg];

    if (st == STATE_1)
    {
        lexeme *l = create_lexeme(buf, type);
        return l;
    }
    else
        return NULL;
}

