#include "identifier.h"

#include <ctype.h>
#include <stdlib.h>

enum _signal
{
    DIGIT,
    ALPHA,
    _,
    OTHER
};
typedef enum _signal signal;

enum _state
{
    INITIAL,
    FINISH,
    FAIL
};
typedef enum _state state;

static signal get_signal(char a)
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
    static state transitions[3][4] = {
        [INITIAL][OTHER] = FAIL,
        [INITIAL][DIGIT] = FAIL,
        [INITIAL][ALPHA] = FINISH,
        [INITIAL][_] = FINISH,
        [FINISH][OTHER] = FAIL,
        [FINISH][DIGIT] = FINISH,
        [FINISH][ALPHA] = FINISH,
        [FINISH][_] = FINISH
    };

    state st = INITIAL;
    int len = 0;
    char buf[LEXEME_SIZE];
    while (st != FAIL)
    {
        signal sg = get_signal(*seq);
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
