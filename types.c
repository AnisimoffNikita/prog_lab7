#include "types.h"

#include <string.h>
#include <malloc.h>

lexeme *create_lexeme(char *s, lexeme_type t)
{
    lexeme *l = malloc(sizeof(lexeme));
    strcpy(l->s, s);
    l->t = t;
    l->l = strlen(s);
    return l;
}
