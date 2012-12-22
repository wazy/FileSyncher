/*
 *  compare timestamps (1 is different)
 *  Version 0.01
 *  ~12/19/12~
 *
*/

#include "client_func.h"

bool TimeComparsion(char *currentFile, char *cachedFile)
{
    printf("Time 1: %s\nTime 2: %s\n", currentFile, cachedFile);

    char s[256], t[256];
    char *token, *token2;
    strcpy(s, currentFile);
    strcpy(t, cachedFile);

    token = strtok(s, ":");
    token2 = strtok(t, ":");
    
    int z = atoi(token);
    int y = atoi(token2);
    int x = z - y;

    if (x != 0)
        return 1; // different hours

    token = strtok(s, ":");
    token2 = strtok(t, ":");

    x = (int *)token - (int *)token2;

    z = atoi(token);
    y = atoi(token2);
    x = z - y;

    if (x != 0)
        return 1; // different minutes

    token = strtok(s, ":");
    token2 = strtok(t, ":");

    x = (int *)token - (int *)token2;

    z = atoi(token);
    y = atoi(token2);
    x = z - y;

    if (x != 0)
        return 1; // different seconds

    return 0; // same time
}
