.PHONY:  all clean

all: clean
	gcc -o lcs largest_consecutive_sum.c
	gcc -o nbita n_bit_binary_addition.c ../helper.c

lcs:
	rm -f lcs
	gcc -o lcs largest_consecutive_sum.c

nbitadd:
	rm -f nbita
	gcc -o nbita n_bit_binary_addition.c ../helper.c

clean:
	rm -f lcs
	rm -f nbita
