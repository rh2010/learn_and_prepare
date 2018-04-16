
.PHONY : all clean edit_distance lcs lis lcsubstring  lpaling_subsequence lpalin_substring

all: clean
	gcc -o ed edit_distance.c
	gcc -o lcs lcs.c
	gcc -o lcsubstring lcsubstring.c
	gcc -o lis lis.c
	gcc -o lpaling_subsequence lpalin_subsequence.c
	gcc -o lpalin_substring lpalin_substring.c

clean:
	rm -f a.out
	rm -f ed
	rm -f lcs
	rm -f lis
	rm -f lcsubstring
	rm -f lpaling_subsequence
	rm -f lpalin_substring

edit_distance:
	rm -f ed
	gcc -o ed edit_distance.c

lcs:
	rm -f lcs
	gcc -o lcs lcs.c

lcsubstring:
	rm -f lcsubstring
	gcc -o lcsubstring lcsubstring.c

lis:
	rm -f lis
	gcc -o lis lis.c

lpaling_subsequence:
	rm -f lpaling_subsequence
	gcc -o lpaling_subsequence lpalin_subsequence.c

lpalin_substring:
	rm -f lpalin_substring
	gcc -o lpalin_substring lpalin_substring.c
