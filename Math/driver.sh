#!/bin/bash

if [ ! -e main ]; then
    echo 'Compiling...'
    cc main.c genOps.c linkedList.c matrix.c UI.c -o main
if [ $? -eq 0 ]; then
    echo 'Program successfully compiled'
else
    echo 'ERROR: COMPILATION FAILED'
    exit 1
fi
fi

echo 'Running program'
echo

./main

if [ ! "$1" = "s" ]; then
    rm main
fi