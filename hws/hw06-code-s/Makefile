CFLAGS = -Wall -g
CC     = gcc $(CFLAGS)

all: ipow_for.s ipow_while.s  coins_main

%.o : %.s			#override automatic compilation of .c to .o

ipow_for.s : ipow_for.c
	gcc -Og -S $<

ipow_while.s : ipow_while.c
	gcc -Og -S $<

coins_main : coins_main.c coins_funcs_asm_complete.s
	$(CC) -o $@ $^


clean:
	rm -f *.o coins_main a.out ipow_for.s ipow_while.s
