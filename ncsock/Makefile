# Компилятор
CC = gcc

# Опции компиляции
CFLAGS = -I/home/lomaster/nesca4/ncsock/include

# Исходные файлы
SOURCES = \
    base.c \
    ftp.c \
    icmp4.c \
    ip4.c \
    socket.c \
    tcp.c \
    test.c

# Объектные файлы
OBJECTS = $(SOURCES:.c=.o)

# Имя исполняемого файла
EXECUTABLE = test

# Правило для сборки исполняемого файла
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	rm -r *.o

# Правило для сборки объектных файлов из исходных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Правило "clean" для удаления временных файлов
clean:
	rm -f $(OBJECTS)

