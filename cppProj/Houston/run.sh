# This script builds the code and runs tests
set -ex
g++ -I. -g -std=c++0x -c AbstractEngine.cpp
g++ -I. -g -std=c++0x -c Engine1.cpp
g++ -I. -g -std=c++0x -c Engine3.cpp
g++ -I. -g -std=c++0x AbstractEngine.o Engine1.o Engine3.o main.cpp
printf "\n----- build done, now running -----\n" 
cat commands.txt | ./a.exe