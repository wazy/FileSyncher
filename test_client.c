// can't guarantee this works correctly

#include <stdio.h>
#include <sys/socket.h>

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

int main(){
	return 0;
}
