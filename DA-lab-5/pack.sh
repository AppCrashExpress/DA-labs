#!/bin/sh

rm -f solution
mkdir solution
cp main.cpp SuffTree.{h,cpp} Makefile solution/
tar -cvf solution.tar solution
rm -r solution

