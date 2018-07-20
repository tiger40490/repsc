# 
set -ex
g++ -I. -std=c++0x -c Engine1.cpp
g++ -I. -std=c++0x Engine1.o main.cpp  
printf "\n----- build done, now running -----\n" 
cat stdin.txt |./a.exe