#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char *extractFactsToFile(char *filename, char *content)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    // Tokenize each word of the content and write it to the file with a newline at the end of each
    char* content_copy = strdup(content);
    char *token = strtok(content_copy, " \t\n");

    while (token != NULL && strcmp(token, "->") != 0)
    {
        fprintf(file, "%s\n", token);
        token = strtok(NULL, " \t\n");
    }
    token = strtok(NULL, " \t\n");

    fclose(file);
    free(content_copy);
    return token;
}

void main(void){
    char* content = "bite cul chatte -> chenolien";
    char* return_value = extractFactsToFile("facts.kbs", content);
    printf("%s\n", return_value);
}