# Activity 15: Loops in Assemby
## Put your name(s) here

In this activity, you will explore how comparisons and jumps can implement simple loops. You will:
- Experiment with C code containing while and for loops and examine the generated assembly code
- Examine how nested loops are created
- Compare the assembly language produced by gcc for isolated functions against the lower-level assembly language produced by disassembling the executable


## Provided Code

This code has "library" files without `main` functions defined, so that we generate just code for each function to examine.
- `Makefile`
    - a makefile to automate the compilation process
- `loops.c`
    - a C code file for function definitions that implement simple loops
- `loops_main.C`
    - a C code file with copies of the functions from `loops.c` but with a
    `main` function that demonstrates each function

### Note about Makefile

The Makefile contains targets that produce the `.s` files as we have done before. It also
contains a target to produce the `.d` files from calling `objdump` on the executable. One
change is that it **keeps** the executable, so that you can run it and see that it works
correctly!

## Your Tasks

Before starting the tasks, examine the contents of the C code files and the Makefile. Make sure you understand what both are supposed to do.

### Task 1: Basic while loops

- Examine the two functions defined in `loops.c`. One of these is from your reading
the other is a slightly more complicated example (it multiplies its inputs using
repeated addition to calculate the product).

- Run `make` and examine the resulting assembly language in `loops.s` for each function. Discuss with your teammates what you see for each example. Make a copy of the `.s` file and add comments as we have done before.

- Compare the code generated for `sum_up` in `loops.s` with the code generated for it in `loops_main.d`. Place the code side by side; which parts are the same and which are different, and why? Add your comments here in the README.

- Do the same with `slow_mult`

### Task 2: Basic for loops

- Create a new function, `sum_up_for`, that uses a for loop instead of a while loop for the `sum_up` task (add this to the `loops.c` and `loops_main.c` files). 
- Compare the assembly code for this new function against the code generated for
the original function. How do they differ?
- Create a new function, `slow_mult_for`, that uses a for loop instead of a while loop for the `slow_mult` task, and compare the results

### Task 3: Connecting by-hand to running code

- Add the functions from the by-hand portion of the activity
to the `loops.c` and `loops_main.c` file
- Work backwards from the third code example to write C code that should generate the assembly code you were given
- Compare your results with what you wrote before: where were your by-hand answers
correct or incorrect?


### Task 4: More complicated functions

Suppose we want a function with the call signature given below:

    int nested_while(int r, int c);

This function should contain two nested for or while loops. The outer loop should iterate over the values from 0 to `r`, and the inner loop should iterate over the
values from 0 to `c`. The function should count how many times the inner loop runs
in all, returning the result
- Define this function, and add it to the `loops.c` and `loops_main.c` files. 
- Try to predict what you think the assembly code will look like for this
- Look at the `loops.s` generated code for this function. Make a copy of the `.s`
file and add comments to it aligning the lines of assembly with the original C code

Finally, suppose we want a function takes in two inputs:

    int if_and_loop(int n, int d);

It should loop over the values from 1 to `n`, and it should add them to a running total if they are divisible by d (if the remainder by d is zero).

- Define this function and add it to `loops.c` and `loops_main.c`.
- Try to predict the assembly code before examining what is generated
- Compare the `loops.s` and `loops_main.d` code for this function with what you predicted. What was the same or different? How close were you to getting the assembly code right?  Add your comments to this README.

### Optional Challenge Task: Effects of Optimization

In our last activity, we looked at how the code changes if we increase the optimization level. Try generating the optimized assembly for `loops.c` and compare
it to the unoptimized versions we worked with before. How does it differ?

## References

- x86-64 jump instruction reference
    - [Steve Friedl's Intel x86 JUMP quick reference](http://unixwiz.net/techtips/x86-jumps.html)
- Assembly language resources (x86, 64-bit)
    - [x86 Assembly/X86 Instructions](http://en.wikibooks.org/wiki/X86_Assembly/X86_Instructions)
    - [X86 Opcode and Instruction Reference](http://ref.x86asm.net/coder64.html)
    - [x86 assembly language](http://en.wikipedia.org/wiki/X86_assembly_language)
    - [x86 instruction listings](http://en.wikipedia.org/wiki/X86_instruction_listings)
- gcc compiler flag references
    - [Compiler Option Summary](https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html)
    - [Index of gcc compiler options](https://gcc.gnu.org/onlinedocs/gcc/Option-Index.html)
- `objdump` resources
    - [Overview of the `objdump` command](https://www.thegeekstuff.com/2012/09/objdump-examples/)
- Makefile guides
  - [An Introduction to Makefiles](https://www.gnu.org/software/make/manual/html_node/Introduction.html), by GNU
  - [Makefile Tutorials and Examples to Build From](https://earthly.dev/blog/make-tutorial/), by Aniket Bhattacharyea
  - [makefile basics - anthony explains](https://www.youtube.com/watch?v=20GC9mYoFGs)
