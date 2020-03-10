#!/bin/bash

workd=$(pwd)
confs=(${workd}/confs/*.conf)

traces=(${workd}/traces/*.trace)

echo "Confs: ${confs[@]}"
echo "Traces: ${traces[@]}"

OUTFOLDER="out"

echo "building..."
make release



echo "running cache-sim with all confs on all traces"
for conf in ${confs[@]}; do
    name="${conf##*/}"
    folder="${workd}/out/${name%.conf}/"

    mkdir -p $folder
    echo "Moving into folder $folder"
    cd $folder
    for trace in ${traces[@]}; do
        echo "${workd}/build/cache-sim $conf $trace"
        ${workd}/build/cache-sim $conf $trace &>/dev/null
    done
    cd $workd

done


