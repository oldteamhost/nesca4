CC = gcc
CFLAGS = -Wall -fPIC -DONLY_COMPILE -march=native -mtune=native -O3 -flto -finline-functions
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
STATIC_LIB = $(BUILD_DIR)/libncsock.a
DYNAMIC_LIB = $(BUILD_DIR)/libncsock.so

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))
EXAMPLES_DIR = examples

all: libraries examples

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC_LIB): $(OBJS)
	ar rcs $@ $(OBJS)

$(DYNAMIC_LIB): $(OBJS)
	$(CC) -shared -o $@ $(OBJS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

libraries: $(STATIC_LIB) $(DYNAMIC_LIB)

examples: libraries
	cd $(EXAMPLES_DIR) && make -j && cd ..

clean:
	rm -rf $(BUILD_DIR) config.status config.log autom4te.cache Makefile config.h
	cd $(EXAMPLES_DIR) && make clean && cd ..

distclean: clean
	rm -f configure

.PHONY: all clean examples distclean libraries
