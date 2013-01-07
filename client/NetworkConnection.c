/*
 *  Establish and transfer the file
 *  Version 0.02
 *  ~1/7/13~
 *
*/

#include "client_func.h"

enum FileTransfer
{
    FileTransferException,
    FileTransferSuccess
};

char buffer[8*1024];
int fileDescriptor;
size_t fileNameLength;

int NetworkConnection(const char *filePath)
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

    fileNameLength = strlen(filePath);
    write(sockfd, &fileNameLength, sizeof(fileNameLength));    /* to send file name size */
    write(sockfd, filePath, fileNameLength);                   /* to send file name itself */

    /* open the user's file */
    fileDescriptor = open(filePath, O_RDONLY);
    while (1)
    {
        /* read data into buffer */
        int bytes_read = read(fileDescriptor, buffer, sizeof(buffer));
        if (bytes_read == 0) /* nothing left to read */
            break;

        if (bytes_read < 0)
            return FileTransferException;

        /*
         *  will loop to write all data, we must make sure to read
         *  and maintain our current position using p
         */
        while (bytes_read > 0)
        {
            int bytes_written = write(sockfd, buffer, bytes_read);
            if (bytes_written <= 0)
                return FileTransferException;

            bytes_read -= bytes_written;
        }
    }
    shutdown(sockfd, 2);
    close(sockfd);
    return FileTransferSuccess;
}