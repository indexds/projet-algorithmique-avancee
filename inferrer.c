#include "inferrer.h"
void AddFact(Rule* new_fact, Fact** first_fact) {
    Fact* fact_node = (Fact*)malloc(sizeof(Fact));
    strcpy(fact_node->data, new_fact->data);
    fact_node->next = *first_fact;
    *first_fact = fact_node;
}

Fact* ForwardChaining(Fact* first_fact, Rule* first_rule) {
    Rule* current_rule = first_rule;

    while (current_rule != NULL) {
        //printf("Current rule : %s \n", current_rule->data);

        if (current_rule->condition == NULL) {
            // Add the conclusion of the rule to the fact base
            AddFact(current_rule, &first_fact);
        } else if (strcmp(current_rule->data, "END") == 0) {
            // Rule data is "END", check if any fact satisfies it
            Fact* current_fact = first_fact;
            while (current_fact != NULL) {
                //printf("%s \n",current_rule->condition->data);
                if (strcmp(current_rule->condition->data, current_fact->data) == 0) {
                    //printf("Fact satisfying END rule: %s\n", current_fact->data);
                    return current_fact;
                }
                current_fact = current_fact->next;
            }
        } else {
            // Check if all conditions of the rule are satisfied
            Condition* current_condition = current_rule->condition;
            bool condition_matched = true;
            Fact* current_fact = first_fact;

            while (current_condition != NULL) {
                bool condition_found = false;
                current_fact = first_fact;  // Reset current_fact to the beginning of the list

                // Loop through facts to find a match for the condition
                while (current_fact != NULL) {
                    if (strcmp(current_fact->data, current_condition->data) == 0) {
                        condition_found = true;
                        break;
                    }
                    current_fact = current_fact->next;
                }

                // If condition not found, mark condition_matched as false
                if (!condition_found) {
                    condition_matched = false;
                    break; // No need to check further conditions for this rule
                }
                current_condition = current_condition->next;  // Move to the next condition
            }

            if (condition_matched) {
                // Add the conclusion of the rule to the fact base
                AddFact(current_rule, &first_fact);
                printf("New fact added: %s \n", current_rule->data);
            }
        }
        current_rule = current_rule->next;
    }
    return NULL;
}
