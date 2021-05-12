#!/usr/bin/sh

filename="result-$(date +%H_%M_%S)"
for i in `seq 1 4000`
do
    echo -n "${i} " >> ${filename}
    ./bench ${i} ${i} >> ${filename}
done
