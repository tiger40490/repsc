executable=a.out
{
  rm -v $executable # in unix, a.exe would be a.out
  g++ -I. -std=c++17 main.cpp -o $executable
  #g++ -I. -std=c++0x board.o Engine1.o Engine2.o main.cpp  
  printf "\n----- build done, now running -----\n" 
  # cat stdin.txt |./a.exe
  ./$executable
} > log.txt 2>&1
cat log.txt
# Based on TickDB run.sh + concretize run.sh
