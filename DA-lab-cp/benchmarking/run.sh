#!/usr/bin/sh

filename="file.txt"

echo -n "" > result

for i in `seq 2000`; do
    echo -n "${i} " >> result
    python3 file-generator.py ${i} > ${filename}
    ./bench ${filename} <(tac ${filename}) >> result
done
