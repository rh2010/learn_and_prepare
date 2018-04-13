.PHONY: all clean insertion inversions merge qsort heap_sort quick selection

all: clean
	gcc -o insertion insertion_sort.c helper.c
	gcc -o inversions inversions.c helper.c
	gcc -o merge merge_sort.c helper.c
	gcc -o qsort quick_sort.c helper.c
	gcc -o heap_sort heap_sort.c helper.c
	gcc -o quick quick.c ../helper.c
	gcc -o selection selection_sort.c ../helper.c

selection:
	rm -f selection
	gcc -o selection selection_sort.c ../helper.c

insertion:
	rm -f insertion
	gcc -o insertion insertion_sort.c helper.c

qsort:
	rm -f qsort
	gcc -o qsort quick_sort.c helper.c

quick:
	rm -f quick
	gcc -o quick quick.c ../helper.c

merge:
	rm -f merge
	gcc -o merge merge_sort.c helper.c

inversions:
	rm -f inversions
	gcc -o inversions inversions.c helper.c

heap_sort:
	rm -f heap_sort
	gcc -o heap_sort heap_sort.c helper.c

clean:
	rm -f selection
	rm -f qsort
	rm -f quick
	rm -f merge
	rm -f inversions
	rm -f insertion
	rm -f heap_sort
