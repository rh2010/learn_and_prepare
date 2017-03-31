/*
 * A program to draw a circle using ASCII characters.
 */
#include <stdio.h>

const int xrange = 40;
const int yrange = 20;
const int radius = 15;

int
main(int argc, char** argv)
{
	int x, y;

	for (y = -yrange; y < yrange; y++) {
		for (x = -xrange; x < xrange; x++) {
			if ((x*x + y*y) > (radius * radius)) {
				printf(" ");
			} else {
				printf("#");
			}
		}
		printf("\n");
	}
	return (0);
}
