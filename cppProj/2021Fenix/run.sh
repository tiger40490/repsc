# Based on TickDB run.sh + concretize run.sh
{
  rm -v a.exe
  g++ -I. -std=c++17 main.cpp
  #g++ -I. -std=c++0x board.o Engine1.o Engine2.o main.cpp  
  printf "\n----- build done, now running -----\n" 
  # cat stdin.txt |./a.exe
  ./a.exe
} > log.txt 2>&1
cat log.txt
