/*
 *  Compare Timestamps
 *  Version 0.03
 *  ~1/8/13~
 *
*/

enum TimeDifference
{
    SAME_LAST_MODIFIED_TIME,
    DIFFERENT_LAST_MODIFIED_TIME
};

#include "client_func.h"

bool TimeComparsion(char *currentFileTimeStamp, char *cachedFileTimeStamp)
{
    token = strtok_r(currentFileTimeStamp, ":", &currentFileTimeStamp);
    token2 = strtok_r(cachedFileTimeStamp, ":", &cachedFileTimeStamp);

    while((token != NULL) && (token2 != NULL))
    {
        HMS_Current    = atoi(token);                          /* HMS = hour/minute/second */
        HMS_Cached     = atoi(token2);
        HMS_Difference = HMS_Current - HMS_Cached;

        if (HMS_Difference != SAME_LAST_MODIFIED_TIME)         /* if zero then the delimit is the same */
            return DIFFERENT_LAST_MODIFIED_TIME;

        token = strtok_r(currentFileTimeStamp, ":", &currentFileTimeStamp);
        token2 = strtok_r(cachedFileTimeStamp, ":", &cachedFileTimeStamp);
    }

    return SAME_LAST_MODIFIED_TIME;                            /* else same times */
}
