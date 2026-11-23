#include <stdio.h>
#include "lexer.h"

int main(void)
{
    char filename[100];

    printf("Enter the C source file name: ");
    if (scanf("%99s", filename) != 1)
        return 1;

    lexical_analyzer(filename);

    return 0;
}
