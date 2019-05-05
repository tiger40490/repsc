g++ -std=c++17 concretize.cpp || exit
./a.exe testC < concretizeCyc.dat || exit
./a.exe test1 < concretize.dat
