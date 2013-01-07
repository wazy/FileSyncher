/* 
 *  GetLastModifiedTime declaration 
 *  for getting last modified time
 *  Version 0.02
 *  ~1/7/13~
 *
*/

#include "client_func.h"

char *GetLastModifiedTime(const char *currentFileStamp)
{
    stat(currentFileStamp, &sb);
    strcpy(s, ctime(&sb.st_mtime));
    token = strtok(s, " ");
    count = 0;
    while (token && count < 3) {
        token = strtok(NULL, " ");
        count++;
    }

    return strdup(token);
}
