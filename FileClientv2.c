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

/*  void pushFileToServer(char *source, char *dest)
{

}
*/
int fileExistIn

int sendall(int s, char *buf, int *len)
{
    int total = 0;        // how many bytes we've sent
    int bytesleft = *len; // how many we have left to send
    int n;

    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    *len = total; // return number actually sent here

    return n==-1?-1:0; // return -1 on failure, 0 on success
} 

int file2socket (FILE *fp, int sockfd)
{
    char buf[8*1024];
    size_t len;
    int ret;

    for (ret = 0;;) {
        len = fread (buf, 1, sizeof (buf), fp);
        if (len == 0) {
            ret = feof (fp);
            break;
        }
        if (!sendall (sockfd, buf, (int *)len)) break;
    }

    return (ret);
}

int main(int argc, char *argv[])
{

}
