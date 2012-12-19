#ifndef CLIENT_FUNC_H
#define CLIENT_FUNC_H

typedef int bool;
#define true  1
#define false 0

// Function declaration for timestamp of two files
bool time(char *file1, char *file2);

/* Function declaration for a function that splits array into 
 * individual tokens
 */
void splitter(char *stat);
