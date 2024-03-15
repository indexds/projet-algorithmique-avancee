#include "inferrer.h"

void AddFact(Rule *new_fact, Fact **first_fact)
{
    Fact *fact_node = (Fact *)malloc(sizeof(Fact));
    strcpy(fact_node->data, new_fact->data);
    fact_node->next = *first_fact;
    *first_fact = fact_node;
}

Fact *ForwardChaining(Fact *first_fact, Rule *first_rule)
{
    Rule *current_rule = first_rule;

    while (current_rule != NULL)
    {

        if (current_rule->condition == NULL)
        {
            // Add the conclusion of the rule to the fact base
            AddFact(current_rule, &first_fact);
        }
        else if (strcmp(current_rule->data, "END") == 0)
        {
            // Rule data is "END", check if any fact satisfies it
            Fact *current_fact = first_fact;
            while (current_fact != NULL)
            {
                if (strcmp(current_rule->condition->data, current_fact->data) == 0)
                {
                    return current_fact;
                }
                current_fact = current_fact->next;
            }
        }
        else
        {
            // Check if all conditions of the rule are satisfied
            Condition *current_condition = current_rule->condition;
            bool condition_matched = true;
            Fact *current_fact = first_fact;

            while (current_condition != NULL)
            {
                bool condition_found = false;
                current_fact = first_fact; // Reset current_fact to the beginning of the list

                // Loop through facts to find a match for the condition
                while (current_fact != NULL)
                {
                    if (strcmp(current_fact->data, current_condition->data) == 0)
                    {
                        condition_found = true;
                        break;
                    }
                    current_fact = current_fact->next;
                }

                // If condition not found, mark condition_matched as false
                if (!condition_found)
                {
                    condition_matched = false;
                    break; // No need to check further conditions for this rule
                }
                current_condition = current_condition->next; // Move to the next condition
            }

            if (condition_matched)
            {
                // Add the conclusion of the rule to the fact base
                AddFact(current_rule, &first_fact);
            }
        }
        current_rule = current_rule->next;
    }

    Fact* not_found  = calloc(1, sizeof(Fact));
    strncpy(not_found->data, "Not Found.", 11);
    return not_found;
}

bool BackwardChaining(Fact *first_fact, Rule *first_rule, char *goal)
{
    // We iterate through the rules. If we find a rule with the same data as the goal, we check if its conditions are satisfied.
    // To do this we iterate through those conditions. If they are true, we do nothing.
    // If they are false, we call BackwardChaining again with the condition as the goal.
    // If a condition has no conditions, we check if it is in the fact base.

    Rule *current_rule = first_rule;

    while(current_rule != NULL){
        if(strcmp(current_rule->data, goal) == 0){

            while(current_rule->condition != NULL){

                if (isFact(first_fact, current_rule->condition->data))
                {
                    return true;
                }

                if (!BackwardChaining(first_fact, first_rule, current_rule->condition->data))
                { // Condition may have other conditions, we check those. If they are false, we return false.
                    return false;
                }

                current_rule->condition = current_rule->condition->next;
                }
        }
        current_rule = current_rule->next;
    }
    return false;
}

bool isFact(Fact* first_fact, char* goal)
{
    Fact* current_fact = first_fact;

    while(current_fact != NULL)
    {
        if(strcmp(current_fact->data, goal) == 0)
        {
            return true;
        }
        current_fact = current_fact->next;
    }
    return false;
}
