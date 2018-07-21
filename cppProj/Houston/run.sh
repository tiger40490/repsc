# 
set -ex
g++ -I. -std=c++0x -c AbstractEngine.cpp
g++ -I. -std=c++0x -c Engine1.cpp
g++ -I. -std=c++0x AbstractEngine.o Engine1.o main.cpp  
printf "\n----- build done, now running -----\n" 
cat commands.txt |./a.exe