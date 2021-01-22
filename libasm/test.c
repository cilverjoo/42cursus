#include <string.h>
#include <stdio.h>

int     main(void)
{
    char    *s1 = "competiteon";
    char    *s2 = "competition";
    int     res;

    res = strcmp(s1, s2);
    printf("%d\n", res);
}