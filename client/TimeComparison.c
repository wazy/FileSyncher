/*
 *  compare timestamps (1 is different)
 *  Version 0.01
 *  ~12/19/12~
 *
*/

#include "client_func.h"

bool TimeComparsion(char *currentFile, char *cachedFile)
{
    /*printf("Time 1: %s	Time 2: %s\n", currentFile, cachedFile);*/

    char s[256], t[256];
    char *token, *token2;
    strcpy(s, currentFile);
    strcpy(t, cachedFile);

    token = strtok(s, ":");
    token2 = strtok(t, ":");
    
    z = atoi(token);
    y = atoi(token2);
    x = z - y;

    if (x != 0)
        return 0; /* different hours */

    token = strtok(s, ":");
    token2 = strtok(t, ":");

    x = (int *)token - (int *)token2;

    z = atoi(token);
    y = atoi(token2);
    x = z - y;

    if (x != 0)
        return 0; /* different minutes */

    token = strtok(s, ":");
    token2 = strtok(t, ":");

    x = (int *)token - (int *)token2;

    z = atoi(token);
    y = atoi(token2);
    x = z - y;

    if (x != 0)
        return 0; /* different seconds */

    return 1; /* same time */
}
