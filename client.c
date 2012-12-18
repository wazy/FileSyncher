/* 
 * Client Version 0.02
 * ~12/08/12~
 *
*/

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
#include <fcntl.h>

 /*   
    struct stat sb;

    stat(argv[1], &sb);
    char s[256];
    strcpy(s, ctime(&sb.st_mtime));
    char *token = strtok(s, " ");
    int count = 0;
    while (token && count < 3) {
        token = strtok(NULL, " ");
        count++;
    }
    printf("%s\n", token);
    strcpy(s, token);
    token = strtok(s, ":");
    count = 0;
    printf("%s\n", token);
    int x = (int *)token - (int *)token;
    printf("%d\n", x);
    while (token && count < 1) {
        token = strtok(NULL, ":");
        count++;
    }
    printf("%s\n", token);

*/

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage is ./client filename\n");
        return 1;
    }
    
    printf("Client program is initializing...\n");

    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
 
   // create socket for client
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) { 
        perror("Socket creation failed.\n") ; 
        return -1 ; 
    } 
     
    // connect to server
    address.sin_family = AF_INET;
    // change this to where you want to connect to
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(7735);
    
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if(result == -1)
    {
        perror("Error occurred in connecting to server.");
        exit(-1);
    }
    
    // write(sockfd, argv[1], sizeof(argv[1])); // to send file name
    // open the user's file

    int fd;
    fd = open(argv[1], O_RDONLY);
   
    char buffer[8*1024];
    while (1) {
        // read data into buffer
        int bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read == 0) // nothing left to read
            break;

        if (bytes_read < 0) // error
            return -1;

        // will loop to write all data, we must make sure to read
        // and maintain our current position using p
        void *p = buffer;
        while (bytes_read > 0) {
            int bytes_written = write(sockfd, buffer, bytes_read);
            if (bytes_written <= 0) {
                return -1;
            }
            bytes_read -= bytes_written;
            p += bytes_written;
        }
    }
    printf("\nTranfer succeeded!\n\n");
    close(sockfd);
    exit(0);
}
