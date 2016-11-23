#include <stdio.h>

#include "fsm.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: syn <file_in> <file_out>\n");
        return 0;
    }
    FILE *fin = fopen(argv[1], "r");
    if (!fin)
    {
        printf("Cannot open file: %s\n", argv[1]);
        return 0;
    }
    FILE *fout = fopen(argv[2], "w");
    if (!fout)
    {
        printf("Cannot open file: %s\n", argv[2]);
        return 0;
    }

    fsm(fin, fout);

    fclose(fin);
    fclose(fout);

    return 0;
}

