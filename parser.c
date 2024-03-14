#include "parser.h"

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

Rule *ruleParser(FILE *file)
{
    char *data = calloc(WORD_SIZE, sizeof(char));
    char *line = calloc(WORD_SIZE * 10, sizeof(char));

    Rule *previous_rule = NULL;
    Rule *first_rule = NULL;

    Condition *previous_condition = NULL;

    while (1)
    {
        line = fgets(line, WORD_SIZE * 10, file);
        if (line == NULL)
        {
            break;
        }

        Rule *current_rule = calloc(1, sizeof(Rule));
        current_rule->next = NULL;
        current_rule->condition = NULL;

        char *token = strtok(line, " \t\n"); // Tokenize the line

        while (token != NULL)
        {
            if (strcmp(token, "->") == 0)
            {
                token = strtok(NULL, " \t\n"); // Move to the next word after "->"
                if (token != NULL)
                {
                    strncpy(current_rule->data, token, WORD_SIZE); // Set the rule data
                }
            }
            else
            {
                Condition *current_condition = calloc(1, sizeof(Condition));
                current_condition->next = NULL;
                strncpy(current_condition->data, token, WORD_SIZE); // Set condition data

                if (current_rule->condition == NULL)
                {
                    current_rule->condition = current_condition; // First condition of the rule
                }
                else
                {
                    if (previous_condition != NULL)
                    {
                        previous_condition->next = current_condition; // Link conditions
                    }
                }
                previous_condition = current_condition;
            }
            token = strtok(NULL, " \t\n"); // Move to the next word
        }

        if (previous_rule != NULL)
        {
            previous_rule->next = current_rule; // Link rules
        }
        if (first_rule == NULL)
        {
            first_rule = current_rule;
        }
        previous_rule = current_rule;
    }

    free(data);
    free(line);

    return first_rule; // Head of the list
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

void freeRules(Rule *rules)
{
    Rule *current_rule = rules;
    while (current_rule != NULL)
    {
        Condition *current_condition = current_rule->condition;
        while (current_condition != NULL)
        {
            Condition *next_condition = current_condition->next;
            free(current_condition);
            current_condition = next_condition;
        }
        Rule *next_rule = current_rule->next;
        free(current_rule);
        current_rule = next_rule;
    }
}

void freeFacts(Fact *facts)
{
    Fact *current_fact = facts;
    while (current_fact != NULL)
    {
        Fact *next_fact = current_fact->next;
        free(current_fact);
        current_fact = next_fact;
    }
}

void editFactsFile(char* filename, char* content){
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    //Tokenize each word of the content and write it to the file with a newline at the end of each
    char *token = strtok(content, " \t\n");
    while (token != NULL)
    {
        fprintf(file, "%s\n", token);
        token = strtok(NULL, " \t\n");
    }
    fclose(file);
}