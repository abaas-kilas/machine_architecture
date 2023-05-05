CFLAGS = -Wall -g
CC     = gcc $(CFLAGS)

all: verify_main dodiv_main

%.o : %.s			#override automatic compilation of .c to .o

dodiv_main : dodiv_main.c dodiv_badtype.s
	gcc -o $@ $^

verify_main : verify.o verify_main.o
	$(CC) -o $@ $^

verify.o : verify.s
	gcc -Og -c $<		#no debugging symbols, like binary bomb

verify.s : verify.c		#generate assembly
	gcc -Og -S $<

verify_main.o : verify_main.c
	$(CC) -c $<

# quote_data.o : quote_data.s
# 	gcc -Og -c $<		# no debugging symbols, like binary bomb

# quote_data.s : quote_data.c	# generate assembly
# 	gcc -Og -S $<

# quote_main.o : quote_main.c
# 	$(CC) -c $<

# quote_main : quote_main.o quote_data.o
# 	$(CC) -o $@ $^



clean:
	rm -f *.o dodiv_main verify_main verify.s
