#include "../util.h"

/*
 * TODO: Implement Karp Rabin.
 */
void
naive_strstr(char *txt, char *pat)
{
	int i, j, t, p;

	printf("Naive Pattern Search\n");
	assert(txt != NULL);
	assert(pat != NULL);

	t = strlen(txt);
	p = strlen(pat);

	for (i=0; i<= t-p; i++) {
		for (j=0; j < p; j++) {
			if (txt[i+j] != pat[j]) {
				break;
			}
		} // j
		if (j == p) {
			printf("pattern found at %d\n", i);
		}
	} // i
}

void
computelps(char *pat, int *lps, int size)
{
	int len;
	int i;

	lps[0] = 0; // lps[0] is always zero

	i = 1;
	len = 0;

	while (i < size) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		} else { // part[i] != pat[len]
			if (len == 0) {
				lps[i] = 0;
				i++;
			} else {
				// len != 0
				len = lps[len-1];
				// don't increment i here.
			}
		}
	} // end while
}

void
kmp(char *txt, char *pat)
{
	int i, j, t, p;
	int *lps;

	printf("KMP Pattern Search\n");
	assert(txt != NULL);
	assert(pat != NULL);

	t = strlen(txt);
	p = strlen(pat);

	lps = (int *)malloc(sizeof (int) * p);
	if (lps == NULL) {
		printf("Error, No Memory!\n");
		exit(-1);
	}

	computelps(pat, lps, p);

	i = 0;
	j = 0;

	while (i < t) {
		if (pat[j] == txt[i]) {
			i++;
			j++;
		}

		if (j == p) {
			printf("Found pattern at %d\n", (i-j));
			j = lps[j-1]; // reset j, don't go all the way back
		} else if (i < t && pat[j] != txt[i]) {
			if (j == 0) {
				i++;
			} else { // j != 0
				j = lps[j-1];
			}
		} // end of if {} else-if {}
	} // end while

	free(lps);
}

void
karp_rabin(char *txt, char *pat)
{
	printf("Karp Rabin - Pattern Search\n");

	printf("Not Implemented\n");
}

int
main(int argc, char **argv)
{
	char *txt, *pat;

	if (argc != 3) {
		printf("usage: ./a.out <text> <pattern>\n");
		exit(-1);
	}
	txt = argv[1];
	pat = argv[2];

	// naive pattern searching
	naive_strstr(txt, pat);

	// KMP
	kmp(txt, pat);

	// Rabin Karp
	karp_rabin(txt, pat);
}
