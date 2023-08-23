.PHONY: clean
clean:
	-rm a.*

SOURCE = $(shell find . -name "*.c")

CC = clang
CC_DEBUGFLAGS = -Wall -O0 -g
CC_TARGET = ./a.out

EMCC = emcc
EMCC_DEBUGFLAGS = -g -O0
EMCC_TARGET_JS = ./a.js
EMCC_TARGET_HTML = ./a.html
EMCC_PRE_JS = --pre-js emcc.pre.js

NODE = node

build:
	$(CC) -O3 $(SOURCE) -o $(CC_TARGET)

build_debug:
	$(CC) $(CC_DEBUGFLAGS) $(SOURCE) -o $(CC_TARGET)

build_js:
	$(EMCC) -O3 $(SOURCE) $(EMCC_PRE_JS) -o $(EMCC_TARGET_JS)

build_html:
	$(EMCC) -O3 $(SOURCE) $(EMCC_PRE_JS) -o $(EMCC_TARGET_HTML)

build_debug_js:
	$(EMCC) $(EMCC_DEBUGFLAGS) $(SOURCE) $(EMCC_PRE_JS) -o $(EMCC_TARGET_JS)

build_debug_html:
	$(EMCC) $(EMCC_DEBUGFLAGS) $(SOURCE) $(EMCC_PRE_JS) -o $(EMCC_TARGET_HTML)


run: clean build
	$(CC_TARGET)

debug: clean build_debug
	$(CC_TARGET)

node: clean build_js
	$(NODE) $(EMCC_TARGET_JS)

debug_node: clean build_debug_js
	$(NODE) $(EMCC_TARGET_JS)