.PHONY:  all clean

all: clean
	gcc -o lcs longest_consecutive_sum.c
	gcc -o nbita n_bit_binary_addition.c

lcs:
	rm -f lcs
	gcc -o lcs longest_consecutive_sum.c

nbitadd:
	rm -f nbita
	gcc -o nbita n_bit_binary_addition.c

clean:
	rm -f lcs
	rm -f nbita
