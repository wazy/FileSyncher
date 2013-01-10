/* 
 * Server Version 0.06
 * ~1/10/13~
 *
*/

#include "server.h"

int main(void)
{
    serverSocket server;
    serverSocket client;
    /* removing old and creating socket for server on defined port */
    server.socketdescriptor            = socket(AF_INET, SOCK_STREAM, 0);
    server.connection.sin_family       = AF_INET;
    server.connection.sin_addr.s_addr  = htons(INADDR_ANY);
    server.connection.sin_port         = htons(PORT);
    server.len                         = sizeof(server);

    bind(server.socketdescriptor, (struct sockaddr *) &server.connection, server.len);

    printf("Server is initialized and listening for clients..\n");

    /* connection queue and waiting for clients */
    while (1)
    {
        listen(server.socketdescriptor, 5);
        client.len              = sizeof(client);
        client.socketdescriptor = accept(server.socketdescriptor, (struct sockaddr *) &client.connection, &client.len);
        printf("\nClient socket is number = %d.\n\n", client.socketdescriptor - 3) ; 

        pid = fork();
        /* implemented calling a child process to take care of file transfer */
        if (pid == 0)
        {
            /* taking filename here.. far from complete */  
            size_t buffer_size;
            rc = read(client.socketdescriptor, &buffer_size, sizeof(buffer_size)); /* read filename size */
            file = malloc(buffer_size);

            if (file == NULL)
            {
                printf("Malloc failed: unable to continue.\n");
                exit(EXIT_FAILURE);
            }

            rv = read(client.socketdescriptor, file, buffer_size);
            printf("%s\n", file);

            if (rc <= 0) /* no filename received */ 
            {
                printf("The filename was not correctly received.\n");
                exit(EXIT_FAILURE);
            }
            /*
            char *homeDir = getenv("HOME");
            homeDir = strcat(homeDir, "/FileSyncher/test.txt");
            fp1 = fopen(homeDir, "w+"); //static file name for now...
            */
			char storage[1];
			rv = read(client.socketdescriptor, storage, 1);
			
			printf("%s", storage);
			
			
            fp1 = fopen(file, "w+");
            if (file != NULL)
                free(file);
            if (fp1 == NULL)
            {
                printf("ERROR: write permissions are not correct for %s\n", file);
                exit(EXIT_FAILURE);
            }
            printf("\nContent:\n");
            while(1)
            {
                /* recieve from client on client_sockfd */
                rc = recv(client.socketdescriptor, fileArray, sizeof(fileArray), 0);
                /* if nothing left to read end loop */
                if (rc <= 0) 
                    break;

                printf("%s", fileArray);
                x = fwrite(fileArray, rc, 1, fp1);         /* write rc amount of bits */
                if (x < 0) 
                    printf("file write error");
                memset(fileArray, '\0', sizeof(fileArray));    /* clean the array */
            }
            fclose(fp1);
            shutdown(client.socketdescriptor, 2);
            /* write(client_sockfd, "Finished", 1); */
            close(client.socketdescriptor);
            return 0;
        }
    else if (pid < 0) 
        printf("could not transfer");
        
    else /* wait for transfer to finish */
        waitpid(pid, NULL, 0);
    }
    return 0;
}
