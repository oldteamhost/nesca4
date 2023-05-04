CC=g++
CFLAGS=-std=c++11
LIB=-lcurl -pthread -lboost_system -lboost_thread -I hikvision -L hikvision/lib -lhcnetsdk
SRCS=$(wildcard *.cc)
OBJS=$(patsubst %.cc,%.o,$(SRCS))
BIN=nesca

.PHONY: all clean clean-bin

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@ $(LIB)

clean:
	rm -f $(OBJS) $(BIN)

clean-bin:
	rm -f $(OBJS)
