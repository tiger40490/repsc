#!/usr/bin/env bash

pushd $(dirname "${BASH_SOURCE[0]}") 
/bin/rm -fv bin/* 
set -ex
g++ -I. --std=c++0x -c src/ValueObj.cpp -o bin/ValueObj.o
g++ -I. --std=c++0x bin/ValueObj.o  src/main.cpp -o bin/main.out
bin/main.out | tee data/_console_output.log
