g++ -std=c++17 concretize.cpp || exit
./a.exe myTest3 < concretize3.dat || exit
./a.exe myTest2 < concretize2.dat || exit
./a.exe myTest1 < concretize.dat || exit
./a.exe myTestC < concretizeCyc.dat || exit
