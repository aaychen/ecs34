#!/bin/bash
if [ $# -lt 2 ]; then
    echo Usage: ./ cp_mult.sh [src] [dest1] ...
    exit 1
else 
    argNum=2
    while [ $argNum -le $# ]; do
        cp $1 ${!argNum}
        argNum=$((argNum + 1))
    done
    exit 0
fi