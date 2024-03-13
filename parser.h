#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

FILE *openFile(char *filename);

Rule *ruleParser(FILE *file);
Fact *factParser(FILE *file);


#endif