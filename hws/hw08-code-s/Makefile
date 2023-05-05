CFLAGS = -Wall -g
CC     = gcc $(CFLAGS)

all: quote_data.o quote_data.s quote_main smash1 smash2

%.o : %.s			#override automatic compilation of .c to .o

quote_data.o : quote_data.s
	gcc -Og -c $<		# no debugging symbols, like binary bomb

quote_data.s : quote_data.c	# generate assembly
	gcc -Og -S $<

quote_main.o : quote_main.c
	$(CC) -c $<

quote_main : quote_main.o quote_data.o
	$(CC) -o $@ $^

smash1 : smash1.c
	$(CC) -o $@ $^

smash2 : smash2.c
	$(CC) -o $@ $^

clean:
	rm -f *.o *.s quote_main
