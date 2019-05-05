g++ -std=c++17 concretize.cpp || exit
./a.exe myTest3 < concretize3.dat || exit # each cell depends on previous
./a.exe myTest2 < concretize2.dat || exit # long chain
./a.exe myTestC < concretizeCycle.dat || exit
./a.exe myTest1 < concretize1.dat || exit # original data
