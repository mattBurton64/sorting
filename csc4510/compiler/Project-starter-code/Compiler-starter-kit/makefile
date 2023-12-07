all: compiler.o error_handler.o parser.o lille_exception.o scanner.o id_table.o symbol.o token.o id_table_entry.o lille_type.o lille_kind.o
	g++ -o compiler compiler.o parser.o error_handler.o lille_exception.o scanner.o id_table.o symbol.o token.o id_table_entry.o lille_type.o lille_kind.o
	echo Compilation complete.

compiler.o: id_table.o error_handler.o parser.o lille_exception.o scanner.o symbol.o compiler.cpp id_table_entry.o
	g++ -std=c++2a -c compiler.cpp

error_handler.o: lille_exception.o token.o error_handler.h error_handler.cpp 
	g++ -std=c++2a -c error_handler.cpp

id_table.o: id_table.h id_table.cpp
	g++ -std=c++2a -c id_table.cpp

lille_exception.o: lille_exception.h lille_exception.cpp
	g++ -std=c++2a -c lille_exception.cpp

scanner.o: error_handler.o lille_exception.o token.o symbol.o id_table.o id_table_entry.o scanner.h scanner.cpp
	g++ -std=c++2a -c scanner.cpp

symbol.o: symbol.h symbol.cpp
	g++ -std=c++2a -c symbol.cpp

token.o: lille_exception.o symbol.o token.h token.cpp
	g++ -std=c++2a -c token.cpp

parser.o: error_handler.o lille_exception.o scanner.o id_table.o symbol.o token.o parser.h parser.cpp id_table_entry.o
	g++ -g -std=c++2a -c parser.cpp

id_table_entry.o: id_table.o id_table_entry.cpp
	g++ -g -std=c++2a -c id_table_entry.cpp

lille_type.o: lille_type.h lille_type.cpp
	g++ -g -std=c++2a -c lille_type.cpp

lille_kind.o: lille_kind.h lille_kind.cpp
	g++ -g -std=c++2a -c lille_kind.cpp

clean:
	rm *.o 
	echo Clean complete
