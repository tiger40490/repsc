g++ -std=c++17 concretize.cpp || exit
./a.exe myTest1 < concretize.dat || exit
./a.exe myTestC < concretizeCyc.dat || exit
