#ifndef CLIENT_FUNC_H
#define CLIENT_FUNC_H

#include <stddef.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ftw.h>
#include <fcntl.h>
#include <pwd.h>
#include <pthread.h>
#include <limits.h>

#define PORT 7737
#define ADDRESS "127.0.0.1" 

typedef int bool;
#define true  1
#define false 0

/* Function declarations */
bool TimeComparsion(char *currentFileTimeStamp, char *cachedFileTimeStamp);
char *GetLastModifiedTime(const char *currentFileStamp);
int NetworkConnection(const char *filePath);

/* Variables */
struct sockaddr_in address;
struct stat sb;
FILE *fp, *fp1;
pthread_t currentFilesThread;
int sockfd, len, result, HMS_Difference, HMS_Cached, HMS_Current;
int thread1, equalTimes, fileTransferSucceeded, count;
char *fileName, *currentFileTime, *cachedFileTime, *token, *token2;
char s[100], str[400];

#endif
