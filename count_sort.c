#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

#define MAX 10 //the maximum value of an element. (10 means 0-9)

void countElems(int *counts, int *array_A, long length);
void writeArray(int *counts, int *array_A);
void genRandomArray(int *array, long length);
void printCounts(int *counts);
void printArray(int *array, long length);
int print_error(char *msg);


/* main function:
 * gets array length from command line args, allocates a random array of that
 * size, allocates the counts array, the executes step 1 of the CountSort
 * algorithm (countsElem) followed by step 2 (writeArray).
*/
int main(int argc, char **argv) {
    long length = 1000000;   // default value is one million
    int verbose = 0;         // default value is not verbose
    long nThreads = omp_get_num_threads();  // default for this machine

    if (argc == 1) { //checks to ensure we have the correct number of args
        fprintf(stderr, "usage: %s <n> [t] [p]\n", argv[0]);
        fprintf(stderr, "where <n> (required) is the length of the array\n");
        fprintf(stderr, "and [t] (optional) is the number of threads to use\n");
        fprintf(stderr, "and [p] (optional) is a binary value (0/1) setting 'verbose mode'\n");
        return 1;
    }
    else {
        length = strtol(argv[1], NULL, 10);
        if (length < 1) {
            print_error("ERROR: length must be greater than 0");
            return 1;
        }
        if (argc == 3) {
            nThreads = strtol(argv[2], NULL, 10);
            if (nThreads < 1) {
                print_error("ERROR: Must have positive number of threads");
                return 1;
            }
            if (argc == 4) {
                verbose = atoi(argv[3]);
            }
        }
    }
    omp_set_num_threads(nThreads);
    
    srand(10);  //uncomment this line to make random values predictably the same each run
    // srand(time(NULL));  //uncomment this line to have random arrays every run

    //generate random array of elements of specified length
    int *array = malloc(length * sizeof(int));
    if (!array) { 
        print_error("ERROR: malloc failed");
        return 1;
    }

    genRandomArray(array, length);

    //allocate counts array.
    int counts[MAX] = {0};

    //print out array before sort
    if (verbose) {
        printf("array before sort:\n");
        printArray(array, length);
    }
    
    // Run countElems, and time how long it takes
    struct timeval tstart, tend;
    gettimeofday(&tstart, NULL);

    countElems(counts, array, length); //calls step 1
    
    gettimeofday(&tend, NULL);
    double time = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
    printf("Run Time for Phase 1 is %g\n", time);

    // Run writeArray, and time how long it takes
    gettimeofday(&tstart, NULL);

    writeArray(counts, array); //calls step2

    gettimeofday(&tend, NULL);
    time = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
    printf("Run Time for Phase 2 is %g\n", time);

    //print out array after sort
    if (verbose) {
        printf("result after sort:\n");
        printArray(array, length);
    }
    free(array); //free memory

    return 0;
}

/*step 1:
 * compute the frequency of all the elements in the input array and store
 * the associated counts of each element in array counts. The elements in the
 * counts array are initialized to zero prior to the call to this function.
*/
void countElems(int *counts, int *array_A, long length) {
    {
        int val, i, local[MAX] = {0};

        for (i = 0; i < length; i++) {
            val = array_A[i]; //read the value at index i
            local[val]++; //update corresponding location in counts
        }

        for (i = 0; i < MAX; i++) {
            counts[i] = local[i];
        }
 
    }
}


/* step 2:
 * overwrite the input array (array_A) using the frequencies stored in the
 *  array counts
*/
void writeArray(int *counts, int *array_A) {
    int i;

    for (i = 0; i < MAX; i++) { //iterate over the counts array
        int j = 0, amt, start = 0;
        for (j = 0; j < i; j++) {
            start += counts[j];
        }

        amt = counts[i]; //capture frequency of element i
        for (j = start; j < start + amt; j++) {
            array_A[j] = i; //replace value at index j of array_A with i
        }
    }
}


/* helper function: genRandomArray
 * fills an input array of specified length (length) with random 
   values from 0 to MAX-1
*/
void genRandomArray(int *array, long length) {
    int i;
    for (i = 0; i < length; i++) {
        array[i] = rand() % MAX;
    }
}


/*helper function: printCounts
 * prints out all the values in the counts array, separated by spaces
*/
void printCounts(int *counts) {
    int i;
    for (i = 0; i < MAX; i++) {
        printf("%d ", counts[i]);
    }
    printf("\n");
}


/* helper function: printArray
 * prints out all the values in the input array separated by spaces
 */
void printArray(int *array, long length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


/*error handling function: prints out error message*/
int print_error(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(2);
}

