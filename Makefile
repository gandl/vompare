CC =gcc
CFLAGS = -lgmp

got: main.c
	$(CC) $(CFLAGS) -o vompare main.c
