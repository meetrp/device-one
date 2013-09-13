#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define SIZE 1

int
main()
{
    int res = 0;
    char buf[SIZE];

    int fp = open("/dev/ones", O_RDONLY);
    if (fp == -1) {
        printf("error %d\n", errno);
        printf("error %s\n", strerror(errno));
        exit(2);
    }
    memset(&buf, 0, (size_t)SIZE);
    res = read(fp, &buf, SIZE);
    if (! res) {
        printf("error %d\n", errno);
        printf("error %s\n", strerror(errno));
    } else 
        // just for test, printing that one byte.
        printf("0x%x\n", (int)(buf[0]));

    close(fp);
}
