.PHONY: clean
clean:
	-rm a.out

CC = clang
SOURCE = $(shell find . -name "*.c")

build:
	$(CC) $(SOURCE)

run: clean build
	./a.out