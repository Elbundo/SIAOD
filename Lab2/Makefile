CC = gcc
SRCMODULES = mysearch.c my_strct.c ../Lab1/mysort.c
OBJMODULES = $(SRCMODULES: .c=.o)
CFLAGS = -Wall -g

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@
main: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o main
run: main
	./main
