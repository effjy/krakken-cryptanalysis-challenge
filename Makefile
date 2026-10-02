CC ?= cc
CFLAGS ?= -O2 -std=c11 -Wall -Wextra
LDLIBS ?= -pthread

.PHONY: all benchmark kat test clean

all: kat

benchmark: krakken.c krakken.h
	$(CC) $(CFLAGS) -DKRAKKEN_MAIN krakken.c -o krakken-bench $(LDLIBS)

kat: tests/kat.c krakken.c krakken.h
	$(CC) $(CFLAGS) -I. tests/kat.c krakken.c -o krakken-kat $(LDLIBS)

test: kat
	./krakken-kat

clean:
	rm -f krakken-bench krakken-kat
