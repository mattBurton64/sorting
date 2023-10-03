all:	pal.o Memory_cell.o
	g++ -o pal pal.o Memory_cell.o
	echo Compilation complete.

pal.o:	Memory_cell.o pal.cpp
	g++ -std=c++2a -c pal.cpp

Memory_cell.o:	Memory_cell.h Memory_cell.cpp
	g++ -std=c++2a -c Memory_cell.cpp

clean:
	rm pal.o Memory_cell.o
	echo Clean complete
