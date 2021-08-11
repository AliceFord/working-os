#include "cstd.h"
#include "drivers/display.h"

const static char hexTable[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len + 1] = '\0';
}

void clear(char s[]) {
    // int i = 1;
    // do {
    //     s[i - 1] = '\0';
    // } while (s[i] != '\0');
    s[0] = '\0';
}

int strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return *a - *b;
}

void strrev(char s[], int n) {
    for (int i = 0; i < n / 2; i++) {
        char c = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = c;
    }
}

void uint32toa(uint32_t n, char buffer[]) {
    for (int i = 0; i < 8; i++) {
        buffer[i] = hexTable[(n >> i * 4) & 0xf];
    }
    buffer[n - 1] = '\0';
    strrev(buffer, strlen(buffer) - 1);
}
