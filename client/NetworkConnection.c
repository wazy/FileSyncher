/*
 *  Establish and transfer the file
 *  Version 0.05
 *  ~1/13/13~
 *
*/

#include "client_func.h"

int NetworkConnection(void)
{ 
    /* create socket for client */
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) 
    {
        perror("Socket creation failed.\n"); 
        return FileTransferException; 
    } 

    /* connect to server */
    address.sin_family = AF_INET;
    /* change this to where you want to connect to */
    address.sin_addr.s_addr = inet_addr(ADDRESS);
    address.sin_port = htons(PORT);

    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if(result == -1)
    {
        perror("Error occurred in connecting to server.");
        return FileTransferException;
    }

   return sockfd;
}
