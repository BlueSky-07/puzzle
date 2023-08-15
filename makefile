.PHONY: clean
clean:
	-rm a.out

build: main.c
	clang main.c puzzle.c position.c piece.c matrix.c

run: clean build
	./a.out