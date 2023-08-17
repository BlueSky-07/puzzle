.PHONY: clean
clean:
	-rm a.out

CC = clang
SOURCE = $(shell find . -name "*.c")
DEBUGFLAGS = -Wall -O0 -g

build_debug:
	$(CC) $(DEBUGFLAGS) $(SOURCE)

build:
	$(CC) $(SOURCE)

run: clean build
	./a.out

debug: clean build_debug
	./a.out