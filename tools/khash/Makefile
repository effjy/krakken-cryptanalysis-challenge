# Standalone khash build: all Krakken source files are in this directory.
CC ?= cc
PYTHON ?= python3
CFLAGS ?= -O2 -std=c11 -Wall -Wextra -Werror
LDFLAGS ?=
LDLIBS ?= -pthread

# Compile AVX2 in its own translation unit; select it at runtime in khash.c.
ARCH := $(shell uname -m)
ifneq ($(filter x86_64 amd64 i386 i486 i586 i686,$(ARCH)),)
DEFAULT_AVX2 := 1
else
DEFAULT_AVX2 := 0
endif
ENABLE_AVX2 ?= $(DEFAULT_AVX2)

ifeq ($(ENABLE_AVX2),1)
BACKEND_OBJECTS := krakken_multi.o
KHASH_CPPFLAGS := -DKHASH_HAVE_AVX2
else
BACKEND_OBJECTS :=
KHASH_CPPFLAGS :=
endif

.PHONY: all check clean
all: khash

khash: khash.o krakken.o $(BACKEND_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

khash.o: khash.c krakken.h
	$(CC) $(CFLAGS) $(KHASH_CPPFLAGS) -c $< -o $@

krakken.o: krakken.c krakken.h
	$(CC) $(CFLAGS) -c $< -o $@

krakken_multi.o: krakken_multi.c krakken.h
	$(CC) $(CFLAGS) -mavx2 -c $< -o $@

khash-scalar: khash.c krakken.c krakken.h
	$(CC) $(CFLAGS) khash.c krakken.c $(LDFLAGS) -o $@ $(LDLIBS)

libkrakken-reference.so: krakken.c krakken.h
	$(CC) $(CFLAGS) -fPIC -shared krakken.c $(LDFLAGS) -o $@ $(LDLIBS)

check: khash khash-scalar libkrakken-reference.so
	$(PYTHON) test_khash.py

clean:
	rm -f khash khash-scalar libkrakken-reference.so khash.o krakken.o krakken_multi.o
