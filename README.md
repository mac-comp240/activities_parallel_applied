# Activity 24: OpenMP Application Example
## Put your name(s) here

In this activity, you will experiment with applying the OpenMP pragmas we've been studying
to a concrete example, the Count Sort algorithm.

You will:
- Run and time the sequential version of Count Sort on a number of different sizes of inputs
- Add parallel pragmas to make Count Sort run multithreaded
- Time the change in performance and compute the speedup as we add parallelism

## Provided Code

This repository has a simple code file containing the code for Count Sort. The
Makefile specifically includes the OpenMP library so that we can use the pragmas:
a more complex Makefile used to generate assembly code automatically:
- `count_sort.c`
    - Contains the sequential version of the Count Sort algorithm, set up so that
    we can time the two main parts of the algorithm 
- `Makefile`
    - A Makefile that contains extra compiler commands for enabling OpenMP

**Note:** While this code is based on the code provided in _Dive into Systems_, it
has been modified to match the style we've been using more, to simplify it, and
to fit the OpenMP version of it. 

## Your Tasks

### Task 1: Explore the sequential code

- Open `count_sort.c` and read through the code, discussing it with your teammates.
Make sure you understand what the `main`, `countElems` and `writeArray` do, and how
they map onto the pseudocode we looked at earlier.
- Compile and run the program, experimenting with varying the command-line arguments
    - Hint: Don't set `verbose` to 1 unless you have chosen a small value for the array length
- Run the same size array multiple times, and note how the times vary from run to run
- Try switching between the two random seed options on lines 45 and 46
    - `srand` sets the random number generator "seed" to the value passed to it; by
    setting that to a constant we can ensure that the same sequence of "random" values
    is produced each time. Passing it `time(NULL)` ensures a different seed each time,
    which gives a new sequence of values.
    - Change between the two, and then run the program several times: does it make any
    noticable difference in runtime?
- Set the code to use `srand(10)`, and collect data on the running times for each "phase" of the algorithm, for different sizes of arrays
    - Repeat for array sizes of 1 million, 10 million, and 100 million (you can try 1 billion, but it will be very slow)
        - Run the program 5 times, and record the values for Phase 1 and Phase 2 here
        in the README
        - Compute the average, min and max time for each array size

### Task 2: Parallelize `countElems`

This was discussed in your reading, so you can go back to refresh your understanding if you like.

- Note the line in `main` that sets the number of threads based on what the user passed in at the command-line. 
- Add the line below to the `countElems` function, as the first statement inside the function

`#pragma omp parallel default(none) shared(counts, array_A, length)`

This will create the currently specified number of threads, and it sets up the `counts`,
`array_A`, and `length` variables to be shared data across all threads.

- Add curly braces after the `#pragma` line to enclose the entire body of the
function. This means each thread will compute all of these lines. Enclose the declarations of `val`, `i`, and `local`: these variables will each be private to
an individual thread, not shared across threads.

- Add the line below right before the first `for` loop.

`#pragma omp for`

This tells the compiler to split up the iterations of the loop across the currently existing threads, in the default way (chunking). Since each iteration of the `for` loop only reads from shared data, and writes only to private data, we don't need to constrain the threads in any way, they can all run concurrently without any race conditions.

- Add the line below right before the second `for` loop

`#pragma omp critical`

This tells the compiler that the second `for` loop should be considered a "critical section" of code: it can break up the iterations across the different threads, but only one thread may run the code at one time. This is because `counts` is shared data, and
we need to ensure that the threads don't interfere with each other!

- Compile and run this program. Collect data like you did in the previous task about the running time for the `countElems` phase (on the same set of array sizes, and running five times then computing min, max and average). Record the data here.

- What do you see? Is the parallel version always faster? If so, try smaller array values: does it always do better? If not, when does it change? What does this tell you about the usefulness of parallelizing the code, and how much overhead OpenMP adds?

- Compute the speedup and efficiency (see [Section 14.4.1](https://diveintosystems.org/book/C14-SharedMemory/performance_basics.html#_speedup) in _Dive into Systems_) and record the result here.

- Experiment with varying other parameters: what if you change the number of threads assigned? How does that affect the running time? Does the efficiency stay constant across different number of threads?

- Try some of the alternatives from our patternlets for allocating iterations of the first `for` loop to threads. Do any of them make any difference?

- Try changing the `#pragma omp critical` command to `#pragma omp for`. What happens then?

### Task 3: Parallelize `writeArray`

- Add the line below right before the `for` loop in `writeArray` (so that `i`, `counts`, and `array_A` are all shared variables).

`#pragma omp parallel for schedule(dynamic)`

This will parallelize the iterations of the outer loop using the dynamic schedule. 
Remember that the dynamic scheduling assigns each iteration of the `for` loop to the next
idle thread. The thread could be idle because it has never been assigned to an iteration,
or because it has already finished its previous iteration.

- Discuss with your teammates, why does this particular schedule make sense for this particular set of for loops? Record your answer here.

- Rerun your previous experiments, recording the running time for `writeArray` on the
same data sizes (repeating 5 times, etc.). 

- Calculate the speedup and efficiency here.

- Which of the two functions shows better efficiency/speedup?

- What happens if you use the default scheduling on this function? Does it perform worse?

- Suppose we wanted an overall measure of speedup/efficiency for this program, so we
wanted to combine the data from `countElems` and `writeArray`. Do this just by adding
up the raw numbers for the two phases (if you have saved data from an earlier run of
the experiment, you may use it, or else rerun the experiment again!). What is the overall
speedup and efficiency

- (Optional) Try varying the number of threads again. What number of threads gives you
the best overall performance?

## References

- OpenMP Tutorials
    - [_Dive into Systems_, Section 14.7](https://diveintosystems.org/book/C14-SharedMemory/openmp.html)
    - [Geeks for Geeks OpenMP Hello World Program](https://www.geeksforgeeks.org/openmp-hello-world-program/)
    - [IBM Shared and Private Variables in a Parallel Environment](https://www.ibm.com/docs/en/zos/2.2.0?topic=programs-shared-private-variables-in-parallel-environment)
- Command-line arguments in C
    - [*Dive into Systems*, Section 2.9.2](https://diveintosystems.org/book/C2-C_depth/advanced_cmd_line_args.html#_c_cmd_line_args_)
    - [Command-Line Arguments in C/C++, by Geeks for Geeks](https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/)
