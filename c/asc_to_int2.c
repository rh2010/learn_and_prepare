#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
asc_to_int(char *s)
{
    int num = 0;
    int i;
    int neg = 0;


    i = 0;
    // case for -ve integer.
    if (s[i] == '-') {
        neg = 1;
        i++;
    }

    while(s[i] != '\0') {
        num = num * 10 + (s[i] - '0');
        printf("[%d]:%c : %d\n", i, s[i], num);
        i++;
    }

    if (neg) {
        num *= -1;
    }
    return num;
}

int
main(int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: ./a.out <an integer>\n");
        exit(-1);
    }

    printf("The input is: %d\n", asc_to_int(argv[1]));
    return (0);
}
