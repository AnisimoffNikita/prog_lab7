#ifndef TYPES_H
#define TYPES_H

#define LEXEME_SIZE 255

typedef enum
{
    KEYWORD,
    IDENTIFIER,
    INT_CONSTANT,
    FLOAT_CONSTANT,
    CHAR_CONSTANT,
    STRING_LITERAL,
    PUNCTUATOR
} lexeme_type;

typedef struct
{
    char s[LEXEME_SIZE];
    lexeme_type t;
    int l;
} lexeme;

lexeme *create_lexeme(char *s, lexeme_type t);

#endif // TYPES_H
