.PHONY: clean
clean:
	-rm a.out

build: main.c
	clang main.c puzzle.c position.c piece.c matrix.c binary.c logger.c

run: clean build
	./a.out