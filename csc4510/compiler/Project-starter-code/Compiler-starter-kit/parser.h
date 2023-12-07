/*
 * parser.h
 *
 *  Created on: Nov 9, 2023
 *      Author: Matt Burton
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "scanner.h"
#include "symbol.h"
#include "token.h"
#include "error_handler.h"
#include "lille_type.h"
#include "lille_kind.h"
#include "id_table.h"
#include "id_table_entry.h"

using namespace std;

class parser {
private:
	bool debugging {false};			// Set debugging to true to execute statement to help debug the parser, otherwise set to false.

  error_handler* error;
  scanner* scan;
  id_table* id_tab;
  
  void prog();     
  void block(string prog_name, bool prog_ident);     
  void declaration();
  lille_type type();       
  //void param_list();  
  //void param();        
  //vector<id_table_entry*> ident_list();    
  lille_kind param_kind();     
  void statement_list();  
  void statement();        
  void simple_statement();  
  void compound_statement();
  void if_statement();      
  void while_statement();   
  void for_statement();     
  void loop_statement();    
  lille_type range();             
  lille_type expr();              
  lille_type boolean();           
  void relop();             
  lille_type simple_expr();       
  void stringop();          
  lille_type expr2();           
  void addop();             
  lille_type term();              
  void multop();            
  lille_type factor();            
  lille_type primary();           
  lille_type string();
  id_table_entry* ident(bool for_variable);             
  //void ident2();            
  lille_type number();  
  //void digit_seq();         
  //void exp();               
  //void pragma();

public:

  parser(scanner* sc, error_handler* err, id_table* table);

  lille_type program(); // Starts parsing the program
};
#endif /* PARSER_H_ */
