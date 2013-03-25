/*
 * TODO:
 * client sends username, server sends out unique random number in response
 * client encrypts this with the hash of their password
 * then sends it to the server, which verifies the correct hash 
 * 
 */

#include "client_func.h"

/* djb2 algorithm */
unsigned long HashGenerator(char *passphrase)
{
    unsigned long hash = 5381;
    int c;

    while ((c = (*passphrase++)))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash; 
}

int Authenticate(char *user)
{
    unsigned long x;
    int userNameLength;
    int valid = 0;
    /* write username */
    sockfd = NetworkConnection();
    
    userNameLength = strlen(user);
    write(sockfd, &userNameLength, sizeof(userNameLength));
    write(sockfd, user, userNameLength);



    /* receive response from server if valid */
    read(sockfd, &valid, 1);
    
    if (valid)
        printf("valid became one\n");
    
    close(sockfd);
    
    x = HashGenerator(user);
    printf("%lu", x);
    return 0;
}

