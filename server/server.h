#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define PORT 7743


typedef struct
{
    int socketdescriptor;
    unsigned len;
    struct sockaddr_in connection;
}
ServerSocket;

size_t buffer_size;
FILE *fp1;
pid_t pid;
char fileArray[8*1024];
int server_sockfd, client_sockfd, isDirectory, rc, rv, x;
char *file, *user;
unsigned long test1;

#endif
