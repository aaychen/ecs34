#!/bin/bash
if [ $# -lt 5 ]; then
    echo Usage: ./run_steps.sh [executable] [start] [end] [step] [outfile]
    exit 1
else
    runCommand=$1
    A=$2
    B=$3
    S=$4
    outfile=$5
    i=0
    until [ $((A + i * S)) -gt $B ]; do
        if [ $i -eq 0 ]; then
            echo === $((A + i * S)) === > $outfile
        else
            echo === $((A + i * S)) === >> $outfile
        fi
        $runCommand $((A + i * S)) >> $outfile
        i=$((i + 1))
    done
    exit 0
fi