#!/usr/bin/sh

testfile_name="dm-test.txt"
#filename="result-$(date +%H_%M_%S)"
filename="variable-m-res.txt"

for i in `seq 2 400`
do
    python3 gentest.py ${i} 1000 ${testfile_name}
    echo -n "${i} " >> ${filename}
    ./bench < ${testfile_name} >> ${filename}
done
