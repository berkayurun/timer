CC = gcc
CFLAGS = -O3
TARGET = timer

.PHONY: all
all: timer
timer: src/timer.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(TARGET)
