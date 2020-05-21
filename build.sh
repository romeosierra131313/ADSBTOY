 #!/bin/bash

clear

echo clearing

g++ -c main.cpp -I/home/stefan/Desktop/CPP/

echo compiling
 
g++ main.o -o main.exe

echo cleaning up 

rm *.o.gch

echo finished cleaning
echo launching app
 
./main.exe
