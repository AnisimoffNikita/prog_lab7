#include "preprocessor.h"

int is_preprocessor(char *seq)
{
    if (*seq == '/' && *(seq+1) == '/')
        return LINE_COMMENT;
    else if (*seq == '/' && *(seq+1) == '*')
        return MULTILINE_COMMENT_OPEN;
    else if (*seq == '*' && *(seq+1) == '/')
        return MULTILINE_COMMENT_OPEN;
    else if (*seq == '#')
        return PREPROCESSOR;
    else
        return NO;
}
