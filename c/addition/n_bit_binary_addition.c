#include "../util.h"

/*
	Consider the problem of adding two n-bits binary integers, stored in two
	n-element arrays A and B. The sum of the two integers should be stored in
	binary form in an (n + 1)-element array C. State the problem formally and
	write the code for it.
*/

#if 0
/*
    This routine is a lighter version of the generic routine
    n_bit_binary_addition().
    This routine will add two arrays of equal sizes.
 */
static int
n_bit_binary_addition_light(int *arra, int size_a,
					        int *arrb, int size_b,
					        int *arrc, int size_c)
{
	int i, tmp;
    int min_size, max_size;
    int *smaller_arr, *larger_arr;

   min_size = MIN(size_a, size_b);
   max_size = MAX(size_a, size_b);

   if (min_size == size_a) {
       smaller_arr = arra;
       larger_arr = arrb;
   } else {
       smaller_arr = arrb;
       larger_arr = arra;
   }

	printf("%s:%d Size of arrays a: %d, b: %d, c: %d, min: %d, max: %d \n",
           __func__, __LINE__, size_a, size_b, size_c, min_size, max_size);

	if (size_c <= max_size) {
		printf("%s:%d Size of array c is smaller than needed",
				__func__, __LINE__);
		return -1; // failure case
	}

	if (size_c == (max_size + 1)) {
        // inititalize array C.
        for (i = 0; i < size_c; i++) {
            arrc[i] = 0;
        }

        for(i = 0; i < size_a; i++) {
            tmp = arra[i] + arrb[i] + arrc[i];
            arrc[i] = tmp % 2;
            arrc[i+1] = tmp / 2;
        }
	} else {
		printf("%s:%d Size of array c is larger than needed\n",
				__func__, __LINE__);
		return -1; // failure case
    }
}
#endif

/*
 * This routine performs n-bit addition of two arrays.
 */
static int
n_bit_binary_addition(int *arra, int size_a,
					  int *arrb, int size_b,
					  int *arrc, int size_c)
{
	int i, tmp;
    int min_size, max_size;
    int *smaller_arr, *larger_arr;

    min_size = MIN(size_a, size_b);
    max_size = MAX(size_a, size_b);

    if (min_size == size_a) {
        smaller_arr = arra;
        larger_arr = arrb;
    } else {
        smaller_arr = arrb;
        larger_arr = arra;
    }

	printf("%s:%d Size of arrays a: %d, b: %d, c: %d, min: %d, max: %d \n",
           __func__, __LINE__, size_a, size_b, size_c, min_size, max_size);

	if (size_c <= max_size) {
		printf("%s:%d Size of array c is smaller than needed",
				__func__, __LINE__);
		return -1; // failure case
	}

	if (size_c == (max_size + 1)) {
        // inititalize array C.
        for (i = 0; i < size_c; i++) {
            arrc[i] = 0;
        }

        for(i = 0; i < max_size; i++) {
            if (i < min_size) {
                tmp = arra[i] + arrb[i] + arrc[i];
            } else {
                // in the range of max_size - min_size
                tmp = larger_arr[i] + arrc[i];
            }
            arrc[i] = tmp % 2;
            arrc[i+1] = tmp / 2;
        }
	} else {
		printf("%s:%d Size of array c is larger than needed",
				__func__, __LINE__);
		return -1; // failure case
    }
}

int
main(void)
{
    int arra[5] = {1, 0, 1, 0, 1};
    int arrb[3] = {1, 1, 0};
    int arrc[6] = {};
   
    printf("Array A\n");
    print_int_arr_reverse(arra, 5);
    printf("Array B\n");
    print_int_arr_reverse(arrb, 3);

    if (n_bit_binary_addition(arra, (int)(sizeof(arra)/sizeof(int)),
                              arrb, (int)(sizeof(arrb)/sizeof(int)),
                              arrc, (int)(sizeof(arrc)/sizeof(int))) < 0) {
        printf("Failure\n");
        return -1;
    }

    printf("Output Array C\n");
    print_int_arr_reverse(arrc, 6);

}
