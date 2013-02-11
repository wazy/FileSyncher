/* 
 * Client Version 0.09
 * ~1/13/13~
 *
*/

/* "69.85.86.206" */

#define _XOPEN_SOURCE 500
#include "client_func.h"

bool uploadAll = false;
bool updateFile = false;
char tmp[LINE_MAX] = {0};

/*
 * nftw takes this as an argument about what to do
 * what we want is the filename which is in path 
 */
int DirList(const char *path, const struct stat *ptr, int flag, struct FTW *ftwbuf)
{
    isDirectory = 0;
    while (!uploadAll && !updateFile && (fgets(tmp, sizeof(tmp), fp) != NULL))
    {
        if (!strstr(tmp, path))
        {
            printf("Not cached!\n");
            return EXIT_FAILURE;
        }
        len = strlen(tmp)-1;
        if (tmp[len] == '\n')
            tmp[len] = 0;

        /* read filename and last modified time */
        fileName = strtok(tmp, "\t");
        cachedFileTime = strtok(NULL, "\t");
        isDirectory = atoi(strtok(NULL, "\t"));    /* !0 indicates a directory */

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
            currentFileTime = GetLastModifiedTime((const char *) fileName);
            equalTimes = TimeComparsion(currentFileTime, cachedFileTime);

            if (equalTimes)
            {
                fileTransferSucceeded = NetworkConnection(fileName, isDirectory);
                if (!fileTransferSucceeded)
                {
                    printf("\nFATAL: Transfer failed in updating %s.\n", fileName);
                    return EXIT_FAILURE;
                }
                printf("File: %s has been updated.\n", fileName);
            }
            free(currentFileTime);
        }
    }
    /* print the filename and last modified date to .names */
    if (updateFile && fp != NULL)
    {
        currentFileTime = GetLastModifiedTime(path);
        fflush(fp);
        fprintf(fp, "%s\t%s\t%d\tDirectory Level=%d\tFlags=%d\n", path, currentFileTime, ptr->st_mode &S_IFDIR, ftwbuf->level, flag);
        free(currentFileTime);
    }

    /* when no cached file exists */
    if (uploadAll)
    {
        printf("uploading... %s\n", path);
        /* is directory? */
        if (ptr->st_mode &S_IFDIR)
            isDirectory = 1;

        fileTransferSucceeded = NetworkConnection(path, isDirectory);
        if (!fileTransferSucceeded)
            printf("\nTransfer failed for %s.\n", path);
    }
    return 0;
}

static void *CurrentFilesThread()
{
    /* gets home path and cats the source folder to it */
    char *homeDir = getenv("HOME");
    homeDir = strcat(homeDir, "/FileSyncher/src/");

    /* if we can't get home environment try this */
    if (!homeDir) 
    {
        struct passwd* pwd = getpwuid(getuid());
        if (pwd)
           homeDir = pwd->pw_dir;
           homeDir = strcat(homeDir, "/FileSyncher/src/");
    }

    /* cached file is .names */
    fp = fopen (".names", "rt");

    /* no cached file exists */
    if (fp == NULL)
    {
        printf("\nWARNING: No cached file exists.\n");
        printf("Uploading all files and creating .names file.\n\n");
        uploadAll = true;
        updateFile = true;
        fp = fopen (".names", "w+");
		
		Authenticate("user");
		
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
    if (argc > 1 && !strncmp(argv[1], "--help", sizeof(argv[1])))
    {
        printf("\nThis program will sync your local FileSyncher directory ");
        printf("with the remote server.\n");
        printf("Usage is %s --parameters.\n\n", argv[0]);
        return EXIT_SUCCESS;
    }
    if (argc > 1 && !strncmp(argv[1], "--clean", sizeof(argv[1])))
    {
        printf("\nRemoving .names file and starting from scratch.\n");
        /* delete file here */
        status = remove(".names");
        if (!status)
            printf("Successfully removed... restarting...\n");
        else
        {
            printf("ERROR: .names not successfully removed.\n");
            return EXIT_FAILURE;
        }
    }

    printf("\nClient program is initializing...\n");

    thread1 = pthread_create(&currentFilesThread, NULL, &CurrentFilesThread, NULL);
    if (thread1 != 0)
    {
        printf("Thread creation failed!");
        return EXIT_FAILURE;
    }

    /* let the threads run.. till end */
    pthread_join(currentFilesThread, NULL);

    printf("\n-------Sync succeeded!-------\n\n");
    return 0;
}
