#include "inferrer.h"
#include "app.h"

int main(void)
{
    FILE *factsFile = openFile("facts.kbs");
    FILE *rulesFile = openFile("rules.kbs");

    Rule *rules = ruleParser(rulesFile);
    Fact *facts = factParser(factsFile);

    // //loop through rules and print their data
    // Rule *current_rule = rules;
    // while (current_rule != NULL)
    // {
    //     printf("%s\n", current_rule->data);
    //     while (current_rule->condition != NULL)
    //     {
    //         printf("Condition: %s\n", current_rule->condition->data);
    //         current_rule->condition = current_rule->condition->next;
    //     }
    //     current_rule = current_rule->next;
    // }

    // // loop through facts and print their data
    // printf("===================\n");

    // Fact *current_fact = facts;
    // while (current_fact != NULL)
    // {
    //     printf("%s\n", current_fact->data);
    //     current_fact = current_fact->next;
    // }

    char* bite = ForwardChaining(facts, rules);

    printf("%s\n", bite);
    fclose(factsFile);
    fclose(rulesFile);

    app();
    return 0;
}
