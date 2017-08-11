CC =gcc
CFLAGS = -lgmp

vompare: main.c
	$(CC) $(CFLAGS) -o vompare main.c
