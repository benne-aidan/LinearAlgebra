#!/bin/bash

echo 'Compiling...'
cc main.c genOps.c linkedList.c matrix.c UI.c -o main

if [ $? -eq 0 ]; then
    echo 'Program successfully compiled'
    echo 'Running program'
else
    echo 'ERROR: COMPILATION FAILED'
    exit 1
fi

./main
rm main