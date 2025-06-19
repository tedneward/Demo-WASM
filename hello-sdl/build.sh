#!/bin/bash
emcc -c hellosdl.c -o hellosdl.o -s USE_SDL=2
emcc hellosdl.o -o hellosdl.html -s USE_SDL=2
