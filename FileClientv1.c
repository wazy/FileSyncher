/* 
 *
 * Alpha Version 0.01 
 * ~12/08/12~
 *
 *
 * FileClient.c pushes FILE to server or if file exists pushes 
 * updated or modified version of File 
 *
 */

#include <stdio.h>
#include <stlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MTU_SIZE 1500
#define CHUNK_SIZE 512

File *file;
char *file_data;

// assumes TCP
unsigned char mtu[MTU_SIZE];
int bytes_read;

/*  // if you need a header specifing file size send it here

//Read file contents into buffer
while (( bytes_read = fread(mtu, MTU_SIZE, 1, file)) != EOF )
    if ( send(client, mtu, bytes_read, 0) < bytes_read )
        do_error();
*/

void pushFileToServer(char *source, char *dest)
{

}

int fileExistIn

int main(int argc, char *argv[])
{

}
