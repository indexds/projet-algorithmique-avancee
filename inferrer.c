#include "inferrer.h"

Fact not_found = {.data = "Not Found.", .next = NULL};

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
            if (allConditionsSatisfied(first_fact, current_rule->condition))
            {
                // Add the conclusion of the rule to the fact base
                AddFact(current_rule, &first_fact);
            }
        }
        current_rule = current_rule->next;
    }

    return &not_found;
}

bool BackwardChaining(Fact *first_fact, Rule *first_rule, char *goal)
{
    Rule *current_rule = first_rule;

    while (current_rule != NULL)
    {
        if (strcmp(current_rule->data, goal) == 0)
        {
            // We iterate through the rules. If we find a rule with the same data as the goal, we check if its conditions are satisfied.
            while (current_rule->condition != NULL)
            {

                if (isFact(first_fact, current_rule->condition->data))
                { // If a condition has no conditions, we check if it is in the fact base.
                    return true;
                }

                if (BackwardChaining(first_fact, first_rule, current_rule->condition->data))
                { // Condition may have other conditions, we check those. If they are false, we return false.
                    return true;
                }

                current_rule->condition = current_rule->condition->next;
            }
        }
        current_rule = current_rule->next;
    }
    return false;
}

bool isFact(Fact *first_fact, char *goal)
{
    Fact *current_fact = first_fact;

    while (current_fact != NULL)
    {
        if (strcmp(current_fact->data, goal) == 0)
        {
            return true;
        }
        current_fact = current_fact->next;
    }
    return false;
}

bool allConditionsSatisfied(Fact *first_fact, Condition *first_condition)
{
    Condition *current_condition = first_condition;

    while (current_condition != NULL)
    {
        if (!isFact(first_fact, current_condition->data))
        {
            return false;
        }
        current_condition = current_condition->next;
    }
    return true;
}

void AddFact(Rule *new_fact, Fact **first_fact)
{
    Fact *fact_node = calloc(1, sizeof(Fact));
    strncpy(fact_node->data, new_fact->data, sizeof(fact_node->data) - 1);
    fact_node->next = *first_fact;
    *first_fact = fact_node;
}
