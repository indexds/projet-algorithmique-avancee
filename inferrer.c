#include "inferrer.h"

bool ForwardChaining(Fact *but, Fact **basedefaits) //WIP
{
    printf("forward\n");

    // condition d'arrêt
    if (but->next == NULL)
    {

        return true;
    }
    else
    {
        but = but->next;
        bool InTheBase = false;
        while (basedefaits != NULL)
        {
            if (strcmp(but->data, basedefaits->data) == 0)
            {
                InTheBase = true;
                return ForwardChaining(but, basedefaits);
            }
            basedefaits = basedefaits->next;
        }
        return false;
    }
}