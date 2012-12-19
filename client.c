/* 
 * Client Version 0.03
 * ~12/19/12~
 *
*/

#include "client_func.h"

int count = 0;
char addresses[100000] = {0};
int x;
char *NewLine = "\n";

// ftw takes this as an argument about what to do
// what we want is the file name which is in path
int DirList(const char *path, const struct stat *ptr, int flag)
{
    int dl = strlen(path);
    x = 0;
    while (x < dl)
    {
        addresses[count] = path[x]; // copy file path into address array
        count++;
        x++;
    }
    addresses[count++] = (char) NewLine[0]; // add a new line to separate files
    return 0;
}

int main(int argc, char *argv[])
{
    splitter(NewLine);
    TimeComparsion(NewLine, NewLine);
    if (argc < 2)
    {
        printf("Usage is ./client filename\n");
        return 1;
    }

    printf("Client program is initializing...\n");

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
    // open the user's filei

    if (ftw("/home/daniel/Programming/", DirList, 20) != 0)
    {
        printf("ERROR: directory is invalid or does not exist..\n");
        return -1; // file tree walker failed
    }
    //printf("%s", addresses); // addresses contains the paths

    // each token will contain a file name
    char *token;
    char delimit[] = "\n";

    token = strtok(addresses, delimit);
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, delimit);
    }

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
    printf("\nTransfer succeeded!\n\n");
    close(sockfd);
    exit(0);
}
