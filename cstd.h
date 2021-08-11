#ifndef CSTD_H
#define CSTD_H

#include <stdint.h>

int strlen(char s[]);
void append(char s[], char n);
void clear(char s[]);
int strcmp(const char *a, const char *b);
void strrev(char s[], int n);
void uint32toa(uint32_t n, char buffer[]);

#endif
