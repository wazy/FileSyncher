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
/*    fileNameLength = strlen(filePath);
    write(sockfd, &fileNameLength, sizeof(fileNameLength));             / * to send file name size * /
    write(sockfd, filePath, fileNameLength);                            / * to send file name itself * /

    / * necessary check to prevent unexpected behavior * /
    if (fileIsDirectory > 0)
    {
        fileIsDirectory = 1;                                            / * write 1 to server for directory * /
        write(sockfd, &fileIsDirectory, sizeof(fileIsDirectory));  
    }
    else
    {
        write(sockfd, &fileIsDirectory, sizeof(fileIsDirectory));       / * else this path is for a file * /
        /* open the user's file * /
        fp2 = fopen(filePath, "r");
        if (fp2 == NULL)
            return FileTransferException;

        strcat((char *)filePath, ".temp");                              / * recreate file temporarily * /

        tempFile = fopen(filePath, "w+");
        if (tempFile == NULL)
            return FileTransferException;
        
        / * copy the original file into the new temp file * /
        while((readWriteCount = fread(buffer, 1, sizeof(buffer), fp2)) > 0)
        {
            if (fwrite(buffer, 1, readWriteCount, tempFile) != readWriteCount)
            {
                printf("Error in transferring file!\n");
                return FileTransferException;
            }
        }
        fclose(fp2);
        rewind(tempFile);
        while (1)
        {
            / * read data into buffer * /
            int bytes_read = fread(buffer, 1, sizeof(buffer), tempFile);

            if (bytes_read == 0) /* nothing left to read * /
            {
                printf("%s\n", buffer);
                break;
            }
            if (bytes_read < 0)
                return FileTransferException;
 
            / * will loop to write all data just read in * /
            while (bytes_read > 0)
            {
                int bytes_written = write(sockfd, buffer, bytes_read);
                if (bytes_written <= 0)
                    return FileTransferException;

                bytes_read -= bytes_written;
            }
            memset(buffer, '\0', sizeof(buffer)); 
       }
       fclose(tempFile);
       remove(filePath);
    }
*/

}
