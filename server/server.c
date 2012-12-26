/* 
 * Server Version 0.02
 * ~12/08/12~
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

int main(int argc, char *argv[])
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
    server_address.sin_port = htons(7735);
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
            FILE *fp1;
            fp1 = fopen("./bin/test.txt", "w+"); //static file name for now...
            while(1)
            {
                // the lower the more times we need to loop
                // but if it is to high a small file will not transfer
                char ch[10];
                size_t len;
                len = sizeof(ch);
                // recieve from client on client_sockfd
                rc = recv(client_sockfd, &ch, len, 0);
                // if nothing left to read end loop
                if (rc <= 0) 
                    break;
                // this is only for debugging
                printf("%s", ch );
                fwrite(ch, sizeof(ch), 1, fp1);
            }
            fclose(fp1);
            //shutdown(client_sockfd, 1);
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
