#ifndef TYPES_H
#define TYPES_H

#define LEXEME_SIZE 255

enum _type
{
    KEYWORD,
    IDENTIFIER
};
typedef enum _type type;

struct _lexeme
{
    char s[LEXEME_SIZE];
    type t;
    int l;
};
typedef struct _lexeme lexeme;

lexeme *create_lexeme(char *s, type t);

#endif // TYPES_H
