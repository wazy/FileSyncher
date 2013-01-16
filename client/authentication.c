/*
 * TODO:
 * client sends username, server sends out unique random number in response
 * client encrypts this with the hash of their password
 * then sends it to the server, which verifies the correct hash 
 * 
 */

#include <stdio.h>

/* djb2 algorithm */
unsigned long HashGenerator(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = (*str++)))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main(void)
{
    unsigned long x;
    char *p = "12345";
    x = HashGenerator(p);
    printf("%lu", x);
    return 0;
}

