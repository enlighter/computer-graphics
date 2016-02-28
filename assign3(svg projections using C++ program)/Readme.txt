This program is best compiled using gcc/g++ version >=4.9
If manually compiling on gcc/g++ version < 5.2, compile using the flag
-std=c++11
e.g. g++ -std=c++11 svg-projection.cpp


This folder has an INCLUDED AUTOMATED compile script compile-a3.sh
which when run using './compile-a3.sh' command, compiles the project and creates
a 'svg-projection.out' file

On running the .out file, you will first be asked to enter the obj file name,
so if the obj file is 'cube.obj', then enter
cube.obj
in the prompt asking for obj filename