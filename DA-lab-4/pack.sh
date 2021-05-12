#!/bin/sh

rm -f solution
mkdir solution
cp main.cpp CircularBuffer.h Makefile solution/
tar -cvf solution.tar solution
rm -r solution
