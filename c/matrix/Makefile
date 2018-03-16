.PHONY: all clean

all: clean
	gcc -o matrix_rotate matrix_rotate.c
	gcc -o matrix_transpose matrix_transpose.c

rotate:
	rm -f matrix_rotate
	gcc -o matrix_rotate matrix_rotate.c

transpose:
	rm -f matrix_transpose
	gcc -o matrix_transpose matrix_transpose.c

clean:
	rm -f matrix_rotate
	rm -f matrix_transpose
