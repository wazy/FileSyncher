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

typedef int bool;
#define true  1
#define false 0

/*  variables and functions for client_func_v2 */
// Function declaration for timestamp of two files
bool TimeComparsion(char *currentFile, char *cachedFile);
int count;
int sockfd;
int len;
struct sockaddr_in address;
int result;
int x;

/* Function declaration for a function that splits array into tokens */
char *splitter(char *stat);

// function declaration for sleeping thread
void *SleepingThread();

// function declaration for Current Files Thread
void *CurrentFilesThread();

#endif
