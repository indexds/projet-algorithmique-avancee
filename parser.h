typedef struct Branch
{
    char data[32];
    struct Branch *left_branch;
    struct Branch *right_branch;
} Branch;