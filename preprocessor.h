#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

typedef enum
{
    NO,
    LINE_COMMENT,
    MULTILINE_COMMENT_OPEN,
    MULTILINE_COMMENT_CLOSE,
    PREPROCESSOR
} preprocessor;

int is_preprocessor(char *seq);

#endif // PREPROCESSOR_H
