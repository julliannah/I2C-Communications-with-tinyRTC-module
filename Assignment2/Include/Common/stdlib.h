#ifndef __STDLIB__
#define __STDLIB__

#include <stdint.h>
#include <stdint.h>
char* itoa(int i);    // Converts an integer value to C string
int atoi(char* cstring); // Converts a C string to an integer
char* dectohex(int i);    // Converts an integer to C string in hexadecimal form
void bzero(void* dest, int bytes); // Zeros out a segment of 'bytes' in memory
void delay(uint32_t count);  //This delay function is used to initiate a short pause after executing some actions


#endif
