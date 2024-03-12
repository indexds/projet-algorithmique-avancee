#include "inferrer.h"

bool ForwardChaining(Fact *first_fact, Rule *first_rule) // Tete de liste des faits et des regles
{
    Rule* current_rule = first_rule;

    while(current_rule != NULL){
        printf("%s\n", current_rule->data);
        if(current_rule->condition == NULL){
            return false;
        }

        Fact* current_fact = first_fact;

        while(current_fact != NULL){
            if(strcmp(current_fact->data, current_rule->condition->data) == 0){
                if(current_rule->condition->next == NULL){
                    return true;
                }
                current_rule->condition = current_rule->condition->next;
            }
            current_fact = current_fact->next;
        }

        current_rule = current_rule->next;

    }
    return false;
}