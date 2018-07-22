# This script builds the code and runs tests
set -ex
g++ -I. -g -std=c++17 -c AbstractEngine.cpp
g++ -I. -g -std=c++17 -c Engine1.cpp
g++ -I. -g -std=c++17 -c Engine3.cpp
g++ -I. -g -std=c++17 AbstractEngine.o Engine1.o Engine3.o main.cpp
set +e
printf "\n----- build done, now running -----\n" 
rm -v output.csv
cat commands.txt | ./a.exe