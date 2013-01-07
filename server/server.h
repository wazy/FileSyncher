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

#define PORT 7735

FILE *fp1;
pid_t pid;
char fileArray[8*1024];
int server_sockfd, client_sockfd, server_len, rc, rv, x;
unsigned client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;
char *file;

#endif
