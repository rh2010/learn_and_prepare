#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

char*
itoa_recursive_do(int num, int len)
{
    int i;
    char *s;

    printf("number: %d, length: %d \n", num, len);
    if (num == 0) {
        printf("Allocating\n");
        s = (char *)malloc((len + 1) * sizeof (char));
        assert(s);
        s[len-1] = '\0';
        return s;
    }

    i = num % 10;
    s = itoa_recursive_do(num/10, len+1);

    // we should have the memory from the string after the allocation.
    printf("Filling : %d at [%d] : %d\n", i, len, num);

    s[len] = i + '0';

    printf("str: %s\n", s);
    return s;
}

char*
itoa_recursive(int num)
{
    int flag;
    char *str;

    if (num < 0)
    {
        flag = TRUE;
        num *= -1;
        str = itoa_recursive_do(num, 1);
        str[0] = '-';
    } else {
        str = itoa_recursive_do(num, 0);
    }
    // we need to reverse the string here.
    //
    return str;
}

char*
itoascii(int num)
{
    int i;
    int count = 0;
    int flag;
    int temp = 0;
    char *str = NULL;

    if (num < 0) {
        flag = TRUE;
        num *= -1; // make it positive;
    } else {
        flag = FALSE;
    }

    // calculate how much memory is needed for the string.
    while (num !=0) {
        i = num % 10;
        num /= 10;
        count++;
        temp = temp * 10 + i;
    //    printf("%d: %d: %d\n", num, i, temp);
    }

    //printf("count: %d\n", count + (flag?1:0) + 1);
    // allocate the string
    str = (char *)malloc((count + (flag?1:0) + 1) * sizeof(char));
    if (str == NULL) {
        return NULL;
    }

    // fill in the string
    count = 0;
    // check for -ve sign
    if (flag) {
        str[count++] = '-';
    }

    while (temp != 0) {
        i = temp % 10;
        temp /= 10;
        str[count++] = i + '0';
    }
    str[count] = '\0';

    return str;
}

int
main(int argc, char **argv)
{
    int num;

    if (argc  != 2) {
        printf("usage: ./a.out <a number>\n");
        exit(-1);
    }

    num = atoi(argv[1]);

    printf("Input: %d\n",  num);
    printf("%s\n", itoascii(num));
    printf("Recursive: %s\n", itoa_recursive(num));

    return (0);
}
