#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Reverse all the words in a string.
 * Eg:
 * string a in words the all Reverse.
 */
char *
reverse_words(char *s)
{
    int i, j;
    int words;
    int start, end, word_size;
    char temp;
    unsigned int len = strlen(s);

    i = 0;
    words = 1;
    while(s[i] != '\0') {
        //printf("[%d] : %c\n", i, s[i]);
        i++;
        if (s[i] == ' ') {
            words++;
        }
    }
    //printf("count: %d, words: %d\n", i, words);
    start = 0;
    end = i - 1;

    // reverse the string
    while (start < end) {
        //printf("start: %d, end: %d\n", start, end);
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }

    //printf("String reversal done\n"); 
    i = 0;
    word_size = 0;
    // reserse the words.
    while (words > 0) {
        word_size = 0;
        j = i;
        // i is the starting point for the next word
        while(s[j] != ' ' ) {
            //printf("[%d]: %c\n", j, s[j]);
            //if (s[j] == ' ') {
            //    printf("Space\n");
            //}
            word_size++;
            j++;
            if (s[j] == '\0') {
                printf("EOL\n");
                break;
            }
        }
        //printf("i: %d, j: %d, word_size: %d\n", i, j, word_size);

        word_size -= 1; // adjust for array indexing.

        start = i;
        end = i + word_size;
        //printf("start: %d, end: %d\n", start, end);
        // j is one before the starting of the next word.
        while (start < end) {
            temp = s[start];
            s[start] = s[end];
            s[end] = temp;
            start++;
            end--;
        }

        // move on to the next word
        words--;
        i = j+1;
    }
    printf("Reversal complete\n");

    return s;
}

int
main(int argc, char **argv)
{
    char *s;
    if (argc != 2) {
        printf("usage: ./a.out \"string to reverse\" \n");
        exit(-1);
    }

    s = argv[1];
    printf("String: %s\n", s);
    printf("Words reversed String: %s\n", reverse_words(s));

    return (0);
}
