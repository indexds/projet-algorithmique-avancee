#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

FILE* openFile(char* filename)
{
    FILE* file = fopen(filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier '%s'\n", filename);
        exit(EXIT_FAILURE);
    }


    if (strcmp(filename + strlen(filename) - 4, ".kbs") != 0)
    {
        fprintf(stderr, "Le fichier '%s' n'est pas un fichier .kbs\n", filename);
        exit(EXIT_FAILURE);
    }

    return file;
}

void fileParser(){}

int main(void)
{
    FILE* file = openFile("test.kbs");
    fclose(file);
    return 0;
}