#include "../util.h"

//
// Write a function to count the maximum contiguous 1's and 0's back-to-back
// contiguously.
//
//count_0
//count_1
//max_count
//
//run = 2 *max(count_0, count_1)
//
//max_count = max(run, max_count)

int
max_binary_subarray(int *arr, int size)
{
    int i;
    int last_run = 0;
    bool eval = FALSE;
   	int count_0, count_1, max_count, run;

	count_0 = count_1 = max_count = run = 0;

    for (i = 0; i < size; i++) {
        
		printf("i: %d, arr[i]: %d, count_0: %d, count_1: %d, last_run: %d, eval: %s\n",
				i, arr[i], count_0, count_1, last_run, (eval) ? "TRUE" : "FALSE");

        if (count_0 == 0 && count_1 == 0) {
			printf("First Encounter\n");
            // first encounter
            if (arr[i] == 0) {
                count_0++;
                last_run = 0;
            } else {
                count_1++;
                last_run = 1;
            }
        } else if (count_0 == 0) {
            // we saw '1' earlier
			printf("Saw '1' earlier\n");
            if (arr[i] == 1) {
                count_1++;
            } else {
                count_0++;
                last_run = 0;
                eval = TRUE;
            }
        } else if (count_1 == 0) {
			// we saw '0' earlier
			printf("Saw '0' earlier\n");
			if (arr[i] == 0) {
				count_0++;
			} else {
				count_1++;
                last_run = 1;
				eval = TRUE;
			}
        } else {
            // we have seen both 0's and 1's
			printf("Seen both '1' and '0' earlier\n");
			if (arr[i] == 1) {
				printf("This 1\n");
				if (last_run == 1) {
					count_1++;
				} else {
					// last run was 0, 
					assert(eval == TRUE);
					run = 2 * MIN(count_0, count_1);
					max_count = MAX(run, max_count);

					printf("count_0: %d, count_1: %d\n", count_0, count_1);
					printf("i: %d, current run: %d, max_count: %d\n", i, run, max_count);

					// reset the counters
					count_0 = 1;
					count_1 = 0;
					last_run = 0;
					eval = FALSE;
				}
			} else {
				// arr[i] ==0
				printf("This 0\n");
				if (last_run == 0) {
					count_0++;
				} else {
					// last run was 1, 
					assert(eval == TRUE);
					run = 2 * MIN(count_0, count_1);
					max_count = MAX(run, max_count);

					printf("count_0: %d, count_1: %d\n", count_0, count_1);
					printf("i: %d, current run: %d, max_count: %d\n", i, run, max_count);

					// reset the counters
					count_0 = 0;
					count_1 = 1;
					last_run = 1;
					eval = FALSE;
				}
			}
        }
    } // end for
	
	if (eval == TRUE) {
		run = 2 * MIN(count_0, count_1);
		max_count = MAX(run, max_count);
		
		printf("FINAL-i: %d, current run: %d, max_count: %d\n", i, run, max_count);
	}
	printf("END - i: %d, current run: %d, max_count: %d\n", i, run, max_count);

	return max_count;
}


int
main(int argc, char **argv)
{
	int size;
	int i;
	int *arr;
	int sum = 0;

	if (argc <= 2) {
		printf("Too few arguments\n");
		printf("./a.out <array-size> <array of integers>\n");
		exit(-1);
	}

	size = atoi(argv[1]);

	// the total number of argument should be array-size + 2
	assert(argc == size+2);

	arr = (int *)malloc(sizeof(int) * size);
	if (arr == NULL) {
		printf("No memory for the array\n");
		exit(-1);
	}
	for(i = 0; i < size; i++) {
		arr[i] = atoi(argv[i+2]);
	}
	sum = max_binary_subarray(arr, size);
	printf("The longest sequence is: %d\n", sum);

	return(0);
}


