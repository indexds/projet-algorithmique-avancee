#ifndef INFERRER_H
#define INFERRER_H

#include "parser.h"

Fact *ForwardChaining(Fact *first_fact, Rule *first_rule);
bool BackwardChaining(Fact *first_fact, Rule *first_rule, char *goal);
bool isFact(Fact *first_fact, char *goal);
bool allConditionsSatisfied(Fact *first_fact, Condition *conditions);
void AddFact(Rule *new_fact, Fact **first_fact);

#endif