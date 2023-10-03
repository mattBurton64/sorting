all:	compiler.o error_handler.o lille_exception.o scanner.o id_table.o symbol.o token.o
	g++ -o compiler compiler.o error_handler.o lille_exception.o scanner.o symbol.o token.o
	echo Compilation complete.

compiler.o:	id_table.o error_handler.o lille_exception.o scanner.o symbol.o compiler.cpp
	g++ -std=c++2b -c compiler.cpp

error_handler.o: lille_exception.o token.o error_handler.h error_handler.cpp
	g++ -std=c++2b -c error_handler.cpp

id_table.o:: id_table.h id_table.cpp
	g++ -std=c++2b -c id_table.cpp

lille_exception.o:	lille_exception.h lille_exception.cpp
	g++ -std=c++2b -c lille_exception.cpp

scanner.o: error_handler.o lille_exception.o token.o symbol.o id_table.o scanner.h scanner.cpp
	g++ -std=c++2b -c scanner.cpp

symbol.o: symbol.h symbol.cpp
	g++ -std=c++2b -c symbol.cpp

token.o: lille_exception.o symbol.o token.h token.cpp
	g++ -std=c++2b -c token.cpp

clean:
	rm *.o 
	echo Clean complete
