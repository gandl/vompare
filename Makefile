CC =gcc
CFLAGS = -lgmp -m64

vompare: main.c
	$(CC) $(CFLAGS) -o vompare main.c
test: main.c
	mkdir -p test
	mkdir -p test/in
	mkdir -p test/out
	afl-gcc $(CFLAGS) -o test/vompare_test main.c
