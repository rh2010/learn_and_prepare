# TODO

.PHONY: addition sort

all:
	@cd addition ; gcc n_bit_binary_addition.c ../helper.c -o add
	@cd sorting ; gcc insertion_sort.c helper.c -o sort

addition: addition/n_bit_binary_addition.c helper.c
	@cd addition ; gcc n_bit_binary_addition.c ../helper.c -o add

sort: sorting/insertion_sort.c helper.c
	@cd sorting ; gcc insertion_sort.c helper.c -o sort

clean:
	@cd addition ; rm add
	@cd sorting ; rm sort
