# 
set -ex
g++ -I. -std=c++0x -c Field.cpp
g++ -I. -std=c++0x -c Tick.cpp
g++ -I. -std=c++0x -c Engine1.cpp
g++ -I. -std=c++0x -c Engine2.cpp
#g++ -I. --std=c++0x Field.o test1.cpp && ./a.out
g++ -I. -std=c++0x Field.o Tick.o Engine1.o Engine2.o main.cpp  
printf "\n----- build done, now running -----\n" 
cat stdin.txt |./a.out
#cat stdin.txt |./a.out -Oprint
#cat stdin.txt |./a.out -Oproduct
