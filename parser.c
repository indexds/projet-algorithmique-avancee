#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define WORD_SIZE 255

typedef struct Condition
{
    char data[WORD_SIZE];
    struct Condition *next;
} Condition;

typedef struct Rule
{
    char data[WORD_SIZE];
    struct Rule *next;
    struct Condition *condition;
} Rule;

typedef struct Fact
{
    char data[WORD_SIZE];
    struct Fact *next;
} Fact;


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

    return file;
}

Rule *ruleParser(FILE *file) //WIP
{
    char *data = calloc(WORD_SIZE, sizeof(char));
    char *line = calloc(WORD_SIZE*10, sizeof(char));

    Rule *previous_rule = NULL;
    Rule *first_rule = NULL;

    while (1)
    {
        line = fgets(line, WORD_SIZE*10, file);
        if (line == NULL)
        {
            break;
        }

        Rule *current_rule = calloc(1, sizeof(Rule));
        current_rule->next = NULL;
        current_rule->condition = NULL;

        while(sscanf(line, "%s", data) != EOF){
            if(strcmp(data, "->") == 0){
                sscanf(line, "%s", current_rule->data); //Dernier mot de la ligne, regle à inferer
            }
            else{
                Condition *current_condition = calloc(1, sizeof(Condition));
                strncpy(current_condition->data, data, strlen(data));
                current_condition->next = NULL;

                if(current_rule->condition == NULL){
                    current_rule->condition = current_condition; //Premiere condition de la regle
                }
                else{
                    Condition *previous_condition = current_rule->condition;
                    while(previous_condition->next != NULL){
                        previous_condition = previous_condition->next;
                    }
                    previous_condition->next = current_condition;
                }
            }
        }
    }
    free(data);
    free(line);

    return first_rule; //Tete de liste
}

Fact *factParser(FILE *file){
    char *data = calloc(WORD_SIZE, sizeof(char));

    Fact* previous_fact = NULL;
    Fact* first_fact = NULL;

    while(1){

        if (fscanf(file, "%s", data) == EOF)
        {
            break;
        }

        data[strlen(data) - 1] = '\0'; //Suppression du dernier caractère (;)

        Fact *current_fact = calloc(1, sizeof(Fact));
        strncpy(current_fact->data, data, strlen(data));
        current_fact->next = NULL;

        if(previous_fact != NULL){
            previous_fact->next = current_fact; //Lien entre les faits
        }

        if (first_fact == NULL){
            first_fact = current_fact;
        }

        previous_fact = current_fact;
    }
    return first_fact; //Tete de liste
}





int main(void)
{
    FILE *factsFile = openFile("facts.kbs");
    FILE *rulesFile = openFile("rules.kbs");

    Rule *rules = ruleParser(rulesFile);
    Fact *facts = factParser(factsFile);

    // loop through rules and print their data
    Rule *current_rule = rules;
    while (current_rule != NULL)
    {
        printf("%s\n", current_rule->data);
        current_rule = current_rule->next;
    }

    // loop through facts and print their data
    printf("===================\n");

    Fact *current_fact = facts;
    while (current_fact != NULL)
    {
        printf("%s\n", current_fact->data);
        current_fact = current_fact->next;
    }

    fclose(factsFile);
    fclose(rulesFile);
    return 0;
}
