/* 
 * Client Version 0.05
 * ~1/6/13~
 *
*/

/* "69.85.86.206" */

#define _XOPEN_SOURCE 500
#include "client_func.h"

bool uploadAll = false;
bool updateFile = false;
int thread1, equalTimes, fileTransferSucceeded;
pthread_t currentFilesThread;
char *fileName, *currentFileTime, *cachedFileTime, str[400];
FILE *fp1;

/*
 * nftw takes this as an argument about what to do
 * what we want is the filename which is in path 
 */
int DirList(const char *path, const struct stat *ptr, int flag, struct FTW *ftwbuf)
{
    x = IsFileCached(path);
    if (x)
    {
        printf("match found -> %s\n", path);
        printf(" %s ", ctime(&ptr->st_mtime));
    }
    printf("%d\n", x);
    while(!uploadAll && !updateFile && (fgets(str, sizeof(str), fp) != NULL))
    {
        len = strlen(str)-1;
        if (str[len] == '\n')
            str[len] = 0;

        /* read filename and last modified time */
        fileName = strtok(str, "\t");
        cachedFileTime = strtok(NULL, "\t");

        /* check if the file read from the file is valid or not */
        if ((fp1 = fopen(fileName, "r")) == NULL)
        {
            printf("Invalid filename or ");
            printf("%s has been deleted since last caching.\n", fileName);
            /* DeleteFileOnServer(p); */
        }

        /* if it exists compare its cached time to its current time */
        else
        {
            fclose(fp1);
            /* get its latest modified time and check it to cached */
            currentFileTime = splitter((const char *) fileName);
            equalTimes = TimeComparsion(cachedFileTime, currentFileTime);
            if (!equalTimes)
            {
                printf("File: %s, has been modified.\n", fileName);
                fileTransferSucceeded = NetworkConnection(path);
                if (!fileTransferSucceeded)
                    printf("Connection failed!\n");
                else
                    printf("Transfer succeeded");
                equalTimes = 1;
            }
            free(currentFileTime);
        }
    }

    /* print the filename and last modified date to .names */
    if (updateFile && fp != NULL)
    {
        currentFileTime = splitter(path);
        fprintf (fp, "%s\t%s\tDirectory Level=%d\tFlags=%d\n", path, currentFileTime, ftwbuf->level, flag);
        free(currentFileTime);
    }
    
    /* NYI: when no cached file exists */
    if (uploadAll)
    {
        printf("uploading file... %s\n", path);
        fileTransferSucceeded = NetworkConnection(path);
        if (!fileTransferSucceeded)
            printf("Connection failed!\n");
        else
            printf("Transfer succeeded");
    }
    return 0;
}

bool IsFileCached(const char *path)
{
    char tmp[LINE_MAX]={0};
    while(fp!=NULL && fgets(tmp, sizeof(tmp),fp)!=NULL)
    {
        if (strstr(tmp, path))
        {
            rewind(fp);
            return 1;
         }
    }

    /* if(fp!=NULL) 
        fclose(fp); */
    rewind(fp);
    return 0;
}
static void *CurrentFilesThread()
{
    /* gets home path and cats the source folder to it */
    char *homeDir = getenv("HOME");
    homeDir = strcat(homeDir, "/FileSyncher/bin/");

    /* if we can't get home environment try this */
    if (!homeDir) 
    {
        struct passwd* pwd = getpwuid(getuid());
        if (pwd)
           homeDir = pwd->pw_dir;
           homeDir = strcat(homeDir, "/FileSyncher/bin/");
    }

    /* cached file is .names */
    fp = fopen (".names", "rt");

    /* no cached file exists */
    if (fp == NULL)
    {
        printf("WARNING: No cached file exists.\n");
        uploadAll = true;
        fp = fopen (".names", "w+");
    
        /* this will find all files in the FS directory */
        if (nftw(homeDir, DirList, 20, 0) != 0)
        {
            printf("ERROR: directory is invalid or does not exist..\n");
            return NULL; /* file tree walker failed */
        }
        fclose (fp);
    }
    /* we have a cached file */
    else
    {
        nftw(homeDir, DirList, 20, 0);
        fclose(fp);

        /*
         * open names file for writing
         * toggle the switch to start updating files
         */
        fp = fopen (".names", "w+");
        updateFile = true;
        /* this will find all files in the directory */
        if (nftw(homeDir, DirList, 20, 0) != 0)
        {
            printf("ERROR: directory is invalid or does not exist..\n");
            return NULL; /* file tree walker failed */
        }
        fclose (fp);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    /* -help parameter from argv[1] */
    if (argc > 1 && !strncmp(argv[1], "-help", 100))
    {
        printf("\nThis program will sync your local FileSyncher directory ");
        printf("with the remote server.\n");
        printf("Usage is %s -parameters.\n\n", argv[0]);
        return EXIT_SUCCESS;
    }

    printf("Client program is initializing...\n");

    thread1 = pthread_create(&currentFilesThread, NULL, &CurrentFilesThread, NULL);
    if (thread1 != 0)
    {
        printf("Thread creation failed!");
        return EXIT_FAILURE;
    }

    /* let the threads run.. till end */
    pthread_join(currentFilesThread, NULL);
    
    printf("\n\nSync succeeded!\n\n");
    exit(EXIT_SUCCESS);
}
