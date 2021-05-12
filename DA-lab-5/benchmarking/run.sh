#!/usr/bin/sh

echo "" > result

for i in `seq 7000`; do
    echo -n "${i} " >> result
    python3 chains.py ${i} | ./bench >> result
done
