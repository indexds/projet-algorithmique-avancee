#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define WORD_LIST_SIZE 10
#define WORD_SIZE 255

typedef struct Branch
{
    char data[WORD_SIZE];
    struct Branch *left_branch;
    struct Branch *right_branch;
} Branch;

FILE *openFile(char *filename)
{
    FILE *file = fopen(filename, "r");

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

    printf("Ouverture du fichier '%s' reussie\n", filename);
    return file;
}

void freeWordList(char **wordList)
{
    for (size_t i = 0; i < WORD_LIST_SIZE; i++)
    {
        free(wordList[i]);
    }
    free(wordList);
}

char **lineReader(FILE *file)
{
    char *line = calloc(2048, sizeof(char));

    char **wordList = calloc(WORD_LIST_SIZE, sizeof(char *));
    for (size_t i = 0; i < 10; i++)
    {
        wordList[i] = calloc(WORD_SIZE, sizeof(char));
    }



    char *word = calloc(WORD_SIZE, sizeof(char));

    for (size_t i = 0; i < WORD_LIST_SIZE; i++)
    {
        fscanf(file, "%s", word);

        if (strcmp(word, "->") == 0)
        {
            fscanf(file, "%s", wordList[9]);
            wordList[9][strlen(wordList[9]) - 1] = '\0'; // remove the ';'
            break;
        }
        else
        {
            strncpy(wordList[i], word, strlen(word));
        }

        // empty word variable
        memset(word, 0, WORD_SIZE);
    }
    free(word);

    free(line);
    return wordList;
}

Branch* createBranch(char **wordList)
{
    size_t element_count = 0;
    for(size_t i = 0; i < WORD_LIST_SIZE; i++)
    {
        if(strlen(wordList[i]) > 0)
        {
            element_count++;
        }
    }


    Branch **branch = calloc(element_count, sizeof(Branch));
    for (size_t i = 0; i < element_count; i++)
    {
        branch[i] = calloc(1, sizeof(Branch));
    }

    for(size_t i = 0 ; i < WORD_LIST_SIZE - 1; i++)
    {
        strncpy(branch[i]->data, wordList[i], strlen(wordList[i]));


        if(i < WORD_LIST_SIZE - 1){
            branch[i]->right_branch = branch[i + 1];
            branch[i]->left_branch = branch[WORD_LIST_SIZE - 1];
        }
        else{
            branch[i]->right_branch = NULL; /* !\ A linker avec la prochaine wordlist /!\ */
            branch[i]->left_branch = NULL;
        }

    }
    return branch[0]; //Return leftMostBranch
}

int main(void)
{
    FILE *file = openFile("rules.kbs");


    fclose(file);
    return 0;
}
