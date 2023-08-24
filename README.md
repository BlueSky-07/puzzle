PUZZLE

### QuickStart

1. `make build` or `make build_debug` to include debug info
2. `LOGGER=true LOGGER_LEVEL=verbose ./a.out`

### Wasm on Node.js

0. modify environment variables in `emcc.pre.js`
1. `make build_js` or `make build_debug_js` to include debug info
2. `node a.js`

### Wasm on Web

0. modify environment variables in `emcc.pre.js`
1. `make build_html` or `make build_debug_html` to include debug info
2. use browser to open `a.html`, open console to view output

### Environment Variables

1. `LOGGER`: toggle logger output, value: `on`/`true` to open, `off`/`false` to close; default: `false`
2. `LOGGER_LEVEL`: switch logger output level, value: `error`/`success`/`info`/`verbose`/`debug`; default: `info`

### Development Dependencies

1. `clang` or `gcc`
2. `make` optional
3. `emcc` Emscripten, optional, required when compiling to js or html
4. `node` Node.js, optional, required when running js

### License

MIT