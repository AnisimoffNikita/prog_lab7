#include "fsm.h"

#include <string.h>
#include <ctype.h>

#include "reg_exp.h"
#include "constant.h"
#include "identifier.h"
#include "keyword.h"
#include "preprocessor.h"
#include "punctuator.h"
#include "string_literal.h"

#define BUFFER_SIZE 256

void print_lexeme(FILE *out, char* buf, char* type, int line, int beg, int len)
{
    printf("%s %s %d %d %d\n", buf, type, line, beg, len);
    fprintf(out, "\t<Token>\n");
    fprintf(out, "\t\t<Category_of_token>%s</Category_of_token>\n", type);
    fprintf(out, "\t\t<Name_of_token>%s</Name_of_token>\n", buf);
    fprintf(out, "\t\t<Number_of_line>%d</Number_of_line>\n", line);
    fprintf(out, "\t\t<Position_in_line>%d</Position_in_line>\n", beg);
    fprintf(out, "\t\t<Length_name_of_token>%d</Length_name_of_token>\n", len);
    fprintf(out, "\t</Token>\n");
}

char *get_type(int type)
{
    switch(type)
    {
    case KEYWORD:
        return "Keyword";
    case IDENTIFIER:
        return "Identifier";
    case INT_CONSTANT:
        return "Int constant";
    case FLOAT_CONSTANT:
        return "Float constant";
    case CHAR_CONSTANT:
        return "Char constant";
    case STRING_LITERAL:
        return "String literal";
    case PUNCTUATOR:
        return "Punctuator";
    default:
        return "Null";
    }
}

void fsm(FILE *fin, FILE *fout)
{
    char *buffer = malloc(sizeof(char)*BUFFER_SIZE);
    char *work;

    int is_multiline_comment = 0;

    lexeme *lexemes[5] = {NULL};

    lexeme *result;

    int lines = 1;
    int pos;

    fprintf(fout, "<Lexeme>\n");

    while(fgets(buffer, BUFFER_SIZE, fin))
    {
        pos = 0;
        work = buffer;
        while (*work)
        {
            if (is_multiline_comment)
            {
                while (work && is_preprocessor(work) != MULTILINE_COMMENT_CLOSE)
                {
                    pos++;
                    work++;
                }
                if (work)
                {
                    is_multiline_comment = 0;
                    work += 2;
                    pos += 2;
                }
            }

            int is_prep = is_preprocessor(work);
            if (is_prep)
            {
                if (is_prep == MULTILINE_COMMENT_OPEN)
                    is_multiline_comment = 1;
                break;
            }

            while (*work && isspace(*work))
            {
                pos++;
                work++;
            }
            if (!*work)
                continue;

            lexemes[0] = find_constant(work);
            lexemes[1] = find_identifier(work);
            lexemes[2] = find_keyword(work);
            lexemes[3] = find_punctuator(work);
            lexemes[4] = find_string_literal(work);

            if (lexemes[1] && lexemes[2] && lexemes[1]->l == lexemes[2]->l)
            {
                free(lexemes[1]);
                lexemes[1] = NULL;
            }

            result = get_longest(lexemes, 5);
            if (!result)
            {
                printf("Something gone wrong...\n");
                break;
            }
            else
            {
                print_lexeme(fout, result->s, get_type(result->t), lines, pos, result->l);
                work += result->l;
                pos += result->l;
            }
            for (int i = 0; i < 5; i++)
            {
                if (lexemes[i])
                    free(lexemes[i]);
                lexemes[i] = NULL;
            }
        }
        lines++;
    }
    fprintf(fout, "</Lexeme>\n");
}

