/*
 *  Alpha Version 0.01
 *  ~12/06/12~
 *
 *
 * we can either take requests or ask to update / add a file here
 * it appears that a different function for only file requests should be made
 * this will handle updating or putting files on server
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int update;
FILE *userFile;
FILE *serverFile;

const char *userSentFile;

void uploadFile(char *source, char *dest)
{
    pid_t pid;
    if (!source || !dest)
        printf("problem.. file or dest does not existing");
    
    pid = fork();
    if (pid == 0) // child
        execl("/bin/cp", "/bin/cp", source, dest, (char *)0);
    
    else if (pid < 0) 
        printf("couldn't copy");
        
    else // wait for cp to finish
        waitpid(pid, NULL, 0);
}

int fileExistsOnServer(FILE *serverFile)
{
    // if server file does not exist return False
    if (serverFile == NULL)
        return 0;
    else
        return 1;
}

int updateFile(FILE *userFile, FILE *serverFile) // files can be different but have the same name
{
    char c1[10000], c2[10000]; // needs to be dynamic
    int cmp;
    
    // read into buffer
    while(fgets(c1 , 15, userFile) != NULL)
    {
        continue;
    }

    while(fgets(c2 , 15, serverFile) != NULL)
    {
        continue;
    }
    cmp = strcmp(c1, c2);

    if(cmp == 0)
        return 0; // userFile == serverFile
    else
        return 1; // userFile != serverFile
}

int main(int argc, char *argv[]) 
{
    if (argc == 3)
    {
        if((userFile = fopen(argv[1], "r")) == NULL) /* needs to be updated to take file from user's computer */
        {
            printf("Invalid user file name sent.\n");
            return -1;
        }
        if((serverFile = fopen(argv[2], "r")) == NULL) /* needs to be updated to take file from user's computer */
        {
            printf("Invalid server file name sent.\n");
            return -1;
        }
    
        /*check if file exists on server*/
        if(!strcmp(argv[1], argv[2]))
        {    // update = 1 when file contents are different
            update = updateFile(userFile, serverFile); 
        
            if (update)        // userFile != serverFile
            {
                uploadFile(argv[1], argv[2]);
                printf("Successful Update!\n");
            }
            else             // userFile == serverFile
            {
                printf("Error: File is the exact same!\n");
            }
        }
        else
        {
            // file does not exist on server
            // argv[1] is the file we have to put up
            // argv[2] should be changed to directory
            uploadFile(argv[1], argv[2]);
            printf("Successful Upload!\n");
        }
    }
    else
    {
        return 1;
    }        
    return 0;
}
