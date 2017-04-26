/* 
 *  C Program to Find the Frequency of  Every Word in a 
 *  given String
 *
 *  Very slow algorithm. Never use it
 */
#include <stdio.h>
#include <string.h>
 
void main()
{
    int count = 0, c = 0, i, j = 0, k, space = 0;
    char str[100], p[50][100], str1[20], ptr1[50][100];
    char *ptr;
 
    printf("Enter the string\n");
    scanf(" %[^\n]s", str);
    printf("string length is %lu\n", strlen(str));
    for (i = 0;i<strlen(str);i++)
    {
        if ((str[i] == ' ')||(str[i] == ',')||(str[i] == '.'))
        {
            space++;
        }
    }
    for (i = 0, j = 0, k = 0;j < strlen(str);j++)
    {
		/*
		 * when a space, ',' or a '.' is seen, start a new word.
		 */
        if ((str[j] == ' ')||(str[j] == 44)||(str[j] == 46))  
        {    
            p[i][k] = '\0';
            i++;
            k = 0;
        } else {
			/*
			 * put all the words in p.
			 */
             p[i][k++] = str[j];
		}
    }
    k = 0;
    for (i = 0;i <= space;i++)
    {
        for (j = 0;j <= space;j++)
        {
            if (i == j)
            {
				/*
				 * ptr1 contains all the distinct words.
				 */
                strcpy(ptr1[k], p[i]);
                k++;
                count++;
                break;
            }
            else
            {
                if (strcmp(ptr1[j], p[i]) != 0)
                    continue;
                else
                    break;
            }
        }
    }
    for (i = 0;i < count;i++) 
    {
        for (j = 0;j <= space;j++)
        {
			/*
			 * Each word in ptr1 is compared against all the words in
			 * p, and a count of the word in ptr1 is arrived at.
			 */
            if (strcmp(ptr1[i], p[j]) == 0)
                c++;
        }
		// Print the count of a distinct word in the input string.
        printf("%s -> %d times\n", ptr1[i], c);
        c = 0;
    }
}
