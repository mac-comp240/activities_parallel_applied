CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c99
LFLAGS = -fopenmp


%: %.c
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $*

# $(OBJ): $(OBJ).c
#	$(CC) $(CFLAGS) $(OBJ).c $(LFLAGS)

progs: count_sort

clean:
	rm -f a.out $(OBJ)

