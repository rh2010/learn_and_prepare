.PHONY: all clean insertion inversions merge qsort

all: clean
	gcc -o insertion insertion_sort.c helper.c
	gcc -o inversions inversions.c helper.c
	gcc -o merge merge_sort.c helper.c
	gcc -o qsort quick_sort.c helper.c

insertion:
	rm -f insertion
	gcc -o insertion insertion_sort.c helper.c

qsort:
	rm -f qsort
	gcc -o qsort quick_sort.c helper.c

merge:
	rm -f merge
	gcc -o merge merge_sort.c helper.c

inversions:
	rm -f inversions
	gcc -o inversions inversions.c helper.c

clean:
	rm -f qsort
	rm -f merge
	rm -f inversions
	rm -f insertion
