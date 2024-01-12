CC = gcc
CFLAGS = -Wall -fPIC
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
STATIC_LIB = $(BUILD_DIR)/libncsock.a
DYNAMIC_LIB = $(BUILD_DIR)/libncsock.so

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))
all: $(STATIC_LIB) $(DYNAMIC_LIB)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC_LIB): $(OBJS)
	ar rcs $@ $(OBJS)

$(DYNAMIC_LIB): $(OBJS)
	$(CC) -shared -o $@ $(OBJS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

