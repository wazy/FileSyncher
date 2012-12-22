/* 
 *  boolean splitter declaration 
 *  for splitting timestamps
 *  Version 0.01
 *  ~12/19/12~
 *
*/

#include "client_func.h"

char *splitter(char *currentFileStamp)
{
    struct stat sb;
    stat(currentFileStamp, &sb);
    char s[256];
    strcpy(s, ctime(&sb.st_mtime));
    char *token = strtok(s, " ");
    int count = 0;
    while (token && count < 3) {
        token = strtok(NULL, " ");
        count++;
    }

    return strdup(token);
}
