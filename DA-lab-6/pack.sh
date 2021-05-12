#!/bin/sh

rm -f solution
mkdir solution
cp -r include/ src/ Makefile solution/
rm solution/include/catch2.hpp
mkdir solution/obj
tar -cvf solution.tar solution
rm -r solution

