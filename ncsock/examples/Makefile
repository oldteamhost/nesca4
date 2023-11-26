CC = gcc
CFLAGS = -Wall -g
OUTPUT_DIR = bin
TEST_SRCS = $(wildcard *.c)
NCSOCK_SRCS = $(wildcard ../*.c)
PROGRAMS = $(patsubst %.c,%,$(TEST_SRCS))

all: $(PROGRAMS)

$(PROGRAMS): % : %.c
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $*.c $(NCSOCK_SRCS) -o $(OUTPUT_DIR)/$@

clean:
	rm -rf $(OUTPUT_DIR)

.PHONY: all clean

