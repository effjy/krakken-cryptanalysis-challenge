CC ?= cc
CFLAGS ?= -O2 -std=c11 -Wall -Wextra
LDLIBS ?= -pthread
MATHLIBS ?= -lm

.PHONY: all benchmark kat test avx2-test avx2-benchmark collision-tool collision-tool-avx2 collision-smoke clean

all: kat

benchmark: krakken.c krakken.h
	$(CC) $(CFLAGS) -DKRAKKEN_MAIN krakken.c -o krakken-bench $(LDLIBS)

kat: tests/kat.c krakken.c krakken.h
	$(CC) $(CFLAGS) -I. tests/kat.c krakken.c -o krakken-kat $(LDLIBS)

test: kat
	./krakken-kat

avx2-test: tests/compare_avx2.c krakken.c krakken_multi.c krakken.h
	$(CC) $(CFLAGS) -mavx2 -I. tests/compare_avx2.c krakken.c krakken_multi.c -o krakken-avx2-test $(LDLIBS)
	./krakken-avx2-test

avx2-benchmark: krakken_multi.c
	$(CC) $(CFLAGS) -mavx2 -DKRAKKEN_MAIN krakken_multi.c -o krakken-avx2-bench $(LDLIBS)

collision-tool: experiments/collision/collision_experiment.c krakken.c krakken.h
	$(CC) $(CFLAGS) -I. experiments/collision/collision_experiment.c krakken.c -o krakken-collision $(LDLIBS) $(MATHLIBS)

collision-tool-avx2: experiments/collision/collision_experiment.c krakken.c krakken_multi.c krakken.h
	$(CC) $(CFLAGS) -DKRAKKEN_ENABLE_AVX2 -mavx2 -I. experiments/collision/collision_experiment.c krakken.c krakken_multi.c -o krakken-collision-avx2 $(LDLIBS) $(MATHLIBS)

collision-smoke: collision-tool
	./krakken-collision --rounds 1,8 --bits 16,20 --trials 3 --out collision_results_smoke

clean:
	rm -f krakken-bench krakken-kat krakken-avx2-test krakken-avx2-bench krakken-collision krakken-collision-avx2
