/* 
 * Server Version 0.03
 * ~1/1/13~
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define PORT 7735

int main(void)
{
    // variables
    int server_sockfd, client_sockfd;
    int server_len ;
    int rc ;
    unsigned client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    // removing old and creating socket for server on port 7735
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);
    server_address.sin_port = htons(PORT);
    server_len = sizeof(server_address);

    bind(server_sockfd, (struct sockaddr *) &server_address, server_len);

    printf("Server is initialized and listening for clients..\n");

    // connection queue and waiting for clients
    while (1)
    {
        listen(server_sockfd, 5);

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
        printf("\nClient socket is number = %d.\n\n", client_sockfd) ; 

        pid_t pid;
        pid = fork();
        // implemented calling a child process to take care of file transfer
        if (pid == 0)
        {
            /* 
             * // Tried implementing taking filename here.. NYI   
             * char file[8];
             * recv(client_sockfd, &file, sizeof(file), 0);
             * fp1 = fopen(file, "w+");
            */

            char fileArray[10];
            FILE *fp1;
            char *homeDir = getenv("HOME");
            homeDir = strcat(homeDir, "/FileSyncher/server/test.txt");
            fp1 = fopen(homeDir, "w+"); //static file name for now...
            if (fp1 == NULL)
              printf("ERROR");
            printf("1");
            while(1)
            {
                // recieve from client on client_sockfd
                rc = recv(client_sockfd, fileArray, sizeof(fileArray), 0);
                // if nothing left to read end loop
                if (rc <= 0) 
                    break;

                printf("%s", fileArray);
                int x = fwrite(fileArray, rc, 1, fp1);         // write rc amount of bits
                if (x < 0) 
                    printf("file write error");
                memset(fileArray, '\0', sizeof(fileArray));    // clean the array
            }
            fclose(fp1);
            shutdown(client_sockfd, SHUT_WR);
            //write(client_sockfd, "Finished", 1);
            close(client_sockfd);
            return 0;
        }
    else if (pid < 0) 
        printf("could not transfer");
        
    else // wait for transfer to finish
        waitpid(pid, NULL, 0);
    }
    return 0;
}
