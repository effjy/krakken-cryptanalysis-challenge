# Build khash against the unchanged repository reference sources.
ROOT := ../..
CC ?= cc
PYTHON ?= python3
CFLAGS ?= -O2 -std=c11 -Wall -Wextra -Werror
LDFLAGS ?=
LDLIBS ?= -pthread

# Compile AVX2 as a separate translation unit. Runtime dispatch is in khash.c.
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

khash.o: khash.c $(ROOT)/krakken.h
	$(CC) $(CFLAGS) $(KHASH_CPPFLAGS) -I$(ROOT) -c $< -o $@

krakken.o: $(ROOT)/krakken.c $(ROOT)/krakken.h
	$(CC) $(CFLAGS) -I$(ROOT) -c $< -o $@

krakken_multi.o: $(ROOT)/krakken_multi.c $(ROOT)/krakken.h
	$(CC) $(CFLAGS) -mavx2 -I$(ROOT) -c $< -o $@

khash-scalar: khash.c $(ROOT)/krakken.c $(ROOT)/krakken.h
	$(CC) $(CFLAGS) -I$(ROOT) khash.c $(ROOT)/krakken.c $(LDFLAGS) -o $@ $(LDLIBS)

libkrakken-reference.so: $(ROOT)/krakken.c $(ROOT)/krakken.h
	$(CC) $(CFLAGS) -fPIC -shared -I$(ROOT) $(ROOT)/krakken.c $(LDFLAGS) -o $@ $(LDLIBS)

check: khash khash-scalar libkrakken-reference.so
	$(PYTHON) test_khash.py

clean:
	rm -f khash khash-scalar libkrakken-reference.so khash.o krakken.o krakken_multi.o
