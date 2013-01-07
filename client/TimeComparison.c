/*
 *  Compare Timestamps
 *  Version 0.02
 *  ~1/7/13~
 *
*/

enum TimeDifference
{
    DIFFERENT_LAST_MODIFIED_TIME,
    SAME_LAST_MODIFIED_TIME
};

#include "client_func.h"

bool TimeComparsion(char *currentFileTimeStamp, char *cachedFileTimeStamp)
{
    strcpy(fileTimeCurrent, currentFileTimeStamp);
    strcpy(fileTimeCached, cachedFileTimeStamp);

    while(1)
    {
        token          = strtok(fileTimeCurrent, ":");
        token2         = strtok(fileTimeCached, ":");
        HMS_Current    = atoi(token);                          /* HMS = hour/minute/second */
        HMS_Cached     = atoi(token2);
        HMS_Difference = HMS_Current - HMS_Cached;

        if (HMS_Difference == DIFFERENT_LAST_MODIFIED_TIME)    /* different last modified times */
            return DIFFERENT_LAST_MODIFIED_TIME;
    }
    return SAME_LAST_MODIFIED_TIME;                            /* same time */
}
