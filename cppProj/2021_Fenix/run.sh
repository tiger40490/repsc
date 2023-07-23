executable=a.out
function1(){ # a function to support early return
  [[ -e $executable ]] && rm -v $executable 
  g++ -I. -std=c++17 main.cpp -o $executable || return -1
  #g++ -I. -std=c++0x board.o Engine1.o Engine2.o main.cpp  
  printf "\n----- build done, now running -----\n" 
  # cat stdin.txt |./$executable
  ./$executable
}

function1 > log.txt 2>&1

# good for brief output .. always shows on console, but no pagination for long output
cat log.txt 
less -E log.txt 2>&1 
# good for long output but shows nothing on console for short output
