/* 
 * Client Version 0.04
 * ~12/26/12~
 *
*/

#define _XOPEN_SOURCE 500
#include "client_func.h"

int count = 0;
char *NewLine = "\n";
bool run = true;
int i, m = 0;
bool uploadAll = false;
bool updateFile = false;
int t1, t2;
pthread_t sleepingThread, currentFilesThread;
int equalTimes;
char *fileName, *currentFileTime, *cachedFileTime;
char str[400];
FILE *fp1;

// nftw takes this as an argument about what to do
// what we want is the filename which is in path
int DirList(const char *path, const struct stat *ptr, int flag, struct FTW *ftwbuf)
{
    while(!updateFile && (fgets(str, sizeof(str), fp) != NULL))
    {
        int len = strlen(str)-1;
        if (str[len] == '\n')
            str[len] = 0;

        // read filename and last modified time
        fileName = strtok(str, "\t");
        cachedFileTime = strtok(NULL, "\t");

        // check if the file read from the file is valid or not
        if ((fp1 = fopen(fileName, "r")) == NULL)
        {
            printf("Invalid filename or ");
            printf("%s has been deleted since last caching.\n", fileName);
            //DeleteFileOnServer(p);
        }

        // if it exists compare its cached time to its current time
        else
        {
            fclose(fp1);
            // get its latest modified time and check it
            currentFileTime = splitter((const char *) fileName);
            equalTimes = TimeComparsion(cachedFileTime, currentFileTime);
            if (!equalTimes)
            {
                printf("File: %s, has been modified.\n", fileName);
                //server->sendFile(fileName);
                equalTimes = 1;
            }
        }
    }

    // print the filename and last modified date to .names
    if (updateFile && fp != NULL)
        fprintf (fp, "%s\t%s\n", path, splitter(path));

    // NYI: when no cached file exists
    if (uploadAll)
        //server->sendFile(path);
        printf("uploading file... %s\n", path);

    return 0;
}

static void *CurrentFilesThread()
{
    // gets home path and cats the source folder to it
    char *homeDir = getenv("HOME");
    homeDir = strcat(homeDir, "/FileSyncher/bin/");

    // if we can't get home environment try this
    if (!homeDir) 
    {
        struct passwd* pwd = getpwuid(getuid());
        if (pwd)
           homeDir = pwd->pw_dir;
           homeDir = strcat(homeDir, "/FileSyncher/bin/");
    }

    // cached file is .names
    fp = fopen (".names", "rt");

    // no cached file exists
    if (fp == NULL)
    {
        printf("WARNING: No cached file exists.\n");
        uploadAll = true;
        fp = fopen (".names", "w+");
    
        // this will find all files in the FS directory
        if (nftw(homeDir, DirList, 20, 0) != 0)
        {
            printf("ERROR: directory is invalid or does not exist..\n");
            return NULL; // file tree walker failed
        }
        fclose (fp);
    }
    // we have a cached file
    else
    {
        nftw(homeDir, DirList, 20, 0);
        fclose(fp);

        // open names file for writing
        // toggle the switch to start updating files
        fp = fopen (".names", "w+");
        updateFile = true;
        // this will find all files in the directory
        if (nftw(homeDir, DirList, 20, 0) != 0)
        {
            printf("ERROR: directory is invalid or does not exist..\n");
            return NULL; // file tree walker failed
        }
        fclose (fp);
    }
    return NULL;
}

static void *SleepingThread()
{
    sleep(5);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage is ./client filename\n");
        return 1;
    }

    printf("Client program is initializing...\n");

    t1 = pthread_create(&sleepingThread, NULL, &SleepingThread, NULL);
    if (t1 != 0)
    {
        printf("Thread creation failed!");
        return -1;
    }

    t2 = pthread_create(&currentFilesThread, NULL, &CurrentFilesThread, NULL);
    if (t2 != 0)
    {
        printf("Thread creation failed!");
        return -1;
    }

   // create socket for client
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) 
    {
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
    printf("Waiting to terminate cleanly...\n");
    // let the threads run.. till end
    pthread_join(currentFilesThread, NULL);
    pthread_join(sleepingThread, NULL);

    printf("\nTransfer succeeded!\n\n");
    close(sockfd);
    exit(0);
}

