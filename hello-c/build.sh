#!/bin/bash
emcc -s WASM=1 -o hello.html --emrun hello.c
