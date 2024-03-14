#ifndef inferrer
#define inferrer

#include "parser.h"

Fact* ForwardChaining(Fact *first_fact, Rule *first_rule);
void AddFact(Rule* new_fact, Fact** first_fact);

#endif