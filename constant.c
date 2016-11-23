#include "constant_int.h"

#include <ctype.h>
#include <stdlib.h>

#include "constant_char.h"
#include "constant_float.h"
#include "constant_int.h"
#include "reg_exp.h"

lexeme *find_constant(char *seq)
{
    lexeme *a[3];
    a[0] = find_char_constant(seq);
    a[1] = find_int_constant(seq);
    a[1] = find_floating_constant(seq);
    return get_longest(a, 3);
}


