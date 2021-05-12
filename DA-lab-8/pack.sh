#!/bin/sh

rm -f solution
mkdir solution
cp -r src/ Makefile solution/
mkdir solution/obj
tar -cvf solution.tar solution
rm -r solution

