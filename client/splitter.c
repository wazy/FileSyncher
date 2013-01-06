/* 
 *  boolean splitter declaration 
 *  for splitting timestamps
 *  Version 0.01
 *  ~12/19/12~
 *
*/

#include "client_func.h"

char s[100];
char *token;
int count;

char *splitter(const char *currentFileStamp)
{
    struct stat sb;
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
