/*
 * parser.cpp
 *
 *  Created on: Nov 9, 2023
 *      Author: Matt Burton
 */

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cctype>
#include <cmath>
#include <vector>

#include "symbol.h"
#include "error_handler.h"
#include "token.h"
#include "scanner.h"
#include "lille_exception.h"
#include "parser.h"
#include "lille_type.h"

using namespace std;

// constructor for the parser object
parser::parser(scanner* scan, error_handler* err, id_table* table)
{
  this->scan = scan;
  this->error = err;
  this->id_tab = table;
}

// <prog> ::= program <ident> is <block> ;
void parser::prog()
{
  if (debugging)
    cout << "Parser: entering prog" << endl;
  
  // initialize the program entry for the id_table
  id_table_entry* program_entry;

  // consume the program keyword
  scan->must_be(symbol::program_sym);

  // add the program name to the id table at scope level 0
  program_entry = id_tab->enter_id(scan->this_token(), lille_type::type_prog, lille_kind::unknown, id_tab->scope(), 0, lille_type::type_unknown);

  // store the program name to compare with the identifier at the end of the program
  std::string prog_name = scan->this_token()->get_identifier_value();

  // consume the program name identifier
  scan->must_be(symbol::identifier);
  
  // enter the program's scope
  id_tab->enter_scope();
  if (id_tab->trace_all())
    cout << "Parser: prog() entering the scope for " << prog_name << endl;

  scan->must_be(symbol::is_sym);

  // enter the program's block
  block(prog_name, true);

  scan->must_be(symbol::semicolon_sym);

  // exit the program's scope
  id_tab->exit_scope();
  if (id_tab->trace_all())
    cout << "Parser: prog() exiting the scope for " << prog_name << endl;

  if (debugging)
    cout << "Parser: exiting prog" << endl;
}

// <block> ::= { <declaration> }* begin <statement_list> end [ <ident> ]
void parser::block(std::string block_name, bool prog_ident)
{
  if (debugging)
    cout << "Parser: entering block" << endl;

  // handle a variable amount of declarations for this block
  while (scan->have(symbol::identifier) or scan->have(symbol::procedure_sym) or scan->have(symbol::function_sym))
    declaration();
  
  scan->must_be(symbol::begin_sym);

  // handle the list of statements in this block
  statement_list();

  scan->must_be(symbol::end_sym);

  // an identifier after the end of a block must match the name of the block
  if (scan->have(symbol::identifier))
  {
    // ensure block name matches
    if (scan->this_token()->get_identifier_value() != block_name)
    {
      if (prog_ident)
        error->flag(scan->this_token(), 75); // identifier name must match program name
      else
        error->flag(scan->this_token(), 107); // identifier must match name of the block
    }
    // consume the identifier
    scan->get_token();
  }

  if (debugging)
    cout << "Parser: exiting block" << endl;
}

// <declaration> ::= <ident_list> : [ constant ] <type>[:=<number> | :=<string> | :=<bool>] ;
//                 | procedure <ident> [ ( <param_list> ) ] is <block> ;
//                 | function <ident> [(<param_list>)] return <type> is <block> ;
void parser::declaration()
{ 
  if (debugging)
    cout << "Parser: entering declaration" << endl;
  
  // list of identifier or parameter tokens
  vector<token*> token_list;

  // list of id_table_entry*'s added the the id_table
  vector<id_table_entry*> id_list;

  // boolean to track if there is another identifier
  bool comma_found = false;

  // boolean to track if there is another parameter
  bool semicolon_found = false;

  // type variable used to update the type on each id_table_entry in id_list
  lille_type ty;

  // the name of the identifier associated with a procedure or function
  std::string block_name;

  // handles the declaration of an identifier list
  if (scan->have(symbol::identifier))
  {
    if (id_tab->trace_all())
      cout << "Parser: declaration() declare identifier(s)" << endl;

    // tracks if the variables are constant 
    bool is_const = false;

    // variables to store the initial value of the indentifier(s)
    int i_const;
    float r_const;
    std::string s_const;
    bool b_const;

    // id_list = ident_list(); // unable to make ident_list() work 
    
    // stores the list of indentifiers in token_list
    if (scan->have(symbol::identifier))
    {
      do {
        // adds identifiers to the token list
        if (scan->have(symbol::identifier))
        {
          token_list.push_back(scan->this_token());
          scan->get_token();
        }
        // handles looping for more identifiers
        comma_found = false;
        if(scan->have(symbol::comma_sym))
        {
          scan->get_token();
          comma_found = true;
        }
      } while (comma_found);
    }

    scan->must_be(symbol::colon_sym);

    // handles the optional constant symbol
    if(scan->have(symbol::constant_sym))
    {
      is_const = true;
      scan->get_token();
    }

    // stores the type of the indentifiers as declared
    ty = type();

    // add the list of identifiers to the id_table with the known information
    for (int i = 0; i < token_list.size(); i++)
      id_list.push_back(id_tab->enter_id(token_list[i], ty, is_const ? lille_kind::constant : lille_kind::variable, id_tab->scope(), 0, lille_type::type_unknown));
    if (id_tab->trace_all())
    {
      cout << "Parser: declaration() added indentifiers to id_table" << endl;
      id_tab->dump_id_table(false);
    }

    // handles initializing a constant
    if (is_const)
    {
      if (id_tab->trace_all())
        cout << "Parser: declaration() initialize value" << endl;
      
      scan->must_be(symbol::becomes_sym);

      // the type of the variable must match the type being assigned to it
      // handle integer assignment
      if (scan->have(symbol::integer))
      {
        i_const = scan->this_token()->get_integer_value();
        if (!ty.is_type(lille_type::type_integer))
          error->flag(scan->this_token(), 111);
        scan->get_token();
      }

      // handle real number assignment
      else if (scan->have(symbol::real_num))
      {
        r_const = scan->this_token()->get_real_value();
        if (!ty.is_type(lille_type::type_real))
          error->flag(scan->this_token(), 111);
        scan->get_token();
      }

      // handle string assignment
      else if (scan->have(symbol::strng))
      {
        s_const = scan->this_token()->get_string_value();
        if (!ty.is_type(lille_type::type_string))
          error->flag(scan->this_token(), 111);
        scan->get_token();
      }

      // handle boolean assignment
      else if (scan->have(symbol::true_sym))
      {
        b_const = true;
        if (!ty.is_type(lille_type::type_boolean))
          error->flag(scan->this_token(), 111);
        scan->get_token();
      }
      else if (scan->have(symbol::false_sym))
      {
        b_const = false;
        if (!ty.is_type(lille_type::type_boolean))
          error->flag(scan->this_token(), 111);
        scan->must_be(symbol::boolean_sym);
      }

      // assign the initial value to each identifier in id_list
      for (int i = 0; i < id_list.size(); i++)
        id_list[i]->fix_const(i_const, r_const, s_const, b_const);   
      if (id_tab->trace_all())
      {
        cout << "Parser: declaration() updated indentier(s) value in id_table" << endl;
        id_tab->dump_id_table(false);
      }
    } 
    
    scan->must_be(symbol::semicolon_sym);
  }

  // handle a procedure declaration
  else if (scan->have(symbol::procedure_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: declaration() procedure" << endl;

    scan->must_be(symbol::procedure_sym);

    // add the procedure identifier to the id_table
    id_table_entry* proc_id = id_tab->enter_id(scan->this_token(), lille_type::type_proc, lille_kind::unknown, id_tab->scope(), 0, lille_type::type_unknown);
    if (id_tab->trace_all())
    {
      cout << "Parser: declaration() added procedure to id_table" << endl;
      id_tab->dump_id_table(false);
    }
    block_name = scan->this_token()->get_identifier_value();
    scan->must_be(symbol::identifier);

    // enter the scope of this procedure
    id_tab->enter_scope();
    if (id_tab->trace_all())
      cout << "Parser: declaration() entering the scope for " << block_name << endl;

    // handle declaring parameters for this procedure
    if (scan->have(symbol::left_paren_sym))
    {
      scan->get_token();
      if (!scan->have(symbol::right_paren_sym))
      {
        //param_list(); // cant make param_list work

        // adds parameters to the id_tab and associates them with this procedure
        do {
          // resets the list of identifiers for this parameter type
          token_list.clear();

          // collects the list of identifiers for this parameter type
          do {
            // adds identifiers to the token list
            if (scan->have(symbol::identifier))
            {
              token_list.push_back(scan->this_token());
              scan->get_token();
            }
            // handles looping for more identifiers
            comma_found = false;
            if(scan->have(symbol::comma_sym))
            {
              scan->get_token();
              comma_found = true;
            }
          } while (comma_found);

          scan->must_be(symbol::colon_sym);

          // store the whether these identifiers are reference or value parameters
          lille_kind p_kind = param_kind();

          // store the type of these identifiers as declared in the parameter list
          ty = type();
          
          // handle looping for more parameters
          semicolon_found = false;
          if(scan->have(symbol::semicolon_sym))
          {
            scan->get_token();
            semicolon_found = true;
          }

          // add identifiers to the id_table as parameters associated with this procedure
          for (int i = 0; i < token_list.size(); i++)
          {
            // add this parameter to the id_table
            id_table_entry* param_id = new id_table_entry(token_list[i], ty, p_kind, id_tab->scope(), 0, lille_type::type_unknown);
            id_tab->add_table_entry(param_id);

            // associate this parameter with this procedure
            proc_id->add_param(param_id);
          }
        } while (semicolon_found);
        if (id_tab->trace_all())
        {
          cout << "Parser: declaration() added parameters to the id_table: " << endl;
          id_tab->dump_id_table(false);
        }
      }
      else
        error->flag(scan->this_token(), 135); // expected parameter list
      
      if (!scan->have(symbol::right_paren_sym))
      {
        error->flag(scan->this_token(), 95); // abnormal parameter list ermination
        while (!scan->have(symbol::right_paren_sym))
          scan->get_token();
      }

      scan->must_be(symbol::right_paren_sym);
    }
    scan->must_be(symbol::is_sym);

    // enter the block for this procedure
    block(block_name, false);

    scan->must_be(symbol::semicolon_sym);

    // exit the scope for this procedure
    id_tab->exit_scope();
    if (id_tab->trace_all())
      cout << "Parser: declaration() exiting the scope for " << block_name << endl;
  }

  // handle a function declaration
  else if (scan->have(symbol::function_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: declaration() function" << endl;

    scan->get_token();
    
    //add function entry to the id_table
    id_table_entry* func_id = id_tab->enter_id(scan->this_token(), lille_type::type_func, lille_kind::unknown, id_tab->scope(), 0, lille_type::type_unknown);
    if (id_tab->trace_all())
    {
      cout << "Parser: declaration() added function to id_table" << endl;
      id_tab->dump_id_table(false);
    }
    block_name = scan->this_token()->get_identifier_value();
    scan->must_be(symbol::identifier);

    // enter the scope of this function
    id_tab->enter_scope();
    if (id_tab->trace_all())
      cout << "Parser: declaration() entering the scope for " << block_name << endl;

    // handle parameter declaration
    if (scan->have(symbol::left_paren_sym))
    {
      scan->get_token();
      if (!scan->have(symbol::right_paren_sym))
      {
        //param_list(); // cant make param_lsit work

        // adds the list of identifiers to the id_table as parameters and associates them with this function     
        // handles parameters
        do {
          // resets the identifier list
          token_list.clear();
          // handles lists of identifiers
          do {
            // stores identifier tokens
            if (scan->have(symbol::identifier))
            {
              token_list.push_back(scan->this_token());
              scan->get_token();
            }
            //handles looping for more identifiers
            comma_found = false;
            if(scan->have(symbol::comma_sym))
            {
              scan->get_token();
              comma_found = true;
            }
          } while (comma_found);

          scan->must_be(symbol::colon_sym);

          // function parameters must be pass by value
          lille_kind p_kind = param_kind();
          if (p_kind.is_kind(lille_kind::ref_param))
            error->flag(scan->this_token(), 123);

          // stores the type of the parameter list as declared
          ty = type();
          
          // handles looping for more parameters
          semicolon_found = false;
          if(scan->have(symbol::semicolon_sym))
          {
            scan->get_token();
            semicolon_found = true;
          }

          // add identifiers to the the id_table and associate them with this function
          for (int i = 0; i < token_list.size(); i++)
          {
            // add parameters to id_table
            id_table_entry* param_id = new id_table_entry(token_list[i], ty, p_kind, id_tab->scope(), 0, lille_type::type_unknown);
            id_tab->add_table_entry(param_id);

            // link parameters with this function
            func_id->add_param(param_id);
          }  
        } while (semicolon_found);
      }
      else
        error->flag(scan->this_token(), 135); // expected parameter list

      if (!scan->have(symbol::right_paren_sym))
      {
        error->flag(scan->this_token(), 95); // abnormal parameter list ermination
        while (!scan->have(symbol::right_paren_sym))
          scan->get_token();
      }

      scan->must_be(symbol::right_paren_sym);
    }

    // handle return type for this function
    scan->must_be(symbol::return_sym);
    lille_type return_type= type();
    func_id->fix_return_type(return_type);

    scan->must_be(symbol::is_sym);

    // enter the block for this function
    block(block_name, false);

    scan->must_be(symbol::semicolon_sym);

    // exit the scope for this function
    id_tab->exit_scope();
    if (id_tab->trace_all())
      cout << "Parser: declaration() exiting scope for " << block_name << endl;
  }

  if (debugging)
    cout << "Parser: exiting declaration" << endl;
}

// <type> ::= integer 
//          | real 
//          | string 
//          | boolean
lille_type parser::type() 
{
  if (debugging)
    cout << "Parser: entering type" << endl;

  lille_type return_type;

  if (scan->have(symbol::integer_sym))
  {
    return_type = lille_type::type_integer;
    scan->get_token();
  }
  else if (scan->have(symbol::real_sym))
  {
    return_type = lille_type::type_real;
    scan->get_token();
  }  
  else if (scan->have(symbol::string_sym))
  {
    return_type = lille_type::type_string;
    scan->get_token();
  }
  else 
  {
    return_type = lille_type::type_integer;
    scan->must_be(symbol::boolean_sym);
  }

  if (id_tab->trace_all())
      cout << "Parser: type() type found: " << return_type.to_string() << endl;

  if (debugging)
    cout << "Parser: exiting type" << endl;

  return return_type;
}

// <param_list> ::= <param> { ; <param> }*
/*void parser::param_list()
{
  if (debugging)
    cout << "Parser: entering param_list" << endl;
  
  param();

  while(scan->have(symbol::semicolon_sym))
  {
    scan->must_be(symbol::semicolon_sym);
    param();
  }

  if (debugging)
    cout << "Parser: exiting param_list" << endl;
}

// <param> ::= <ident_list> : <param_kind> <type>
void parser::param()
{
  if (debugging)
    cout << "Parser: entering param" << endl;

  ident_list();
  scan->must_be(symbol::colon_sym);
  param_kind();
  type();

  if (debugging)
    cout << "Parser: exiting param" << endl;
}

// <ident_list> ::= <ident> { , <ident> }*
vector<id_table_entry*> parser::ident_list()
{
  if (debugging)
    cout << "Parser: entering ident_list" << endl;

  vector<id_table_entry*> id_list;
  id_list.push_back(ident());
  while(scan->have(symbol::comma_sym))
  {
    scan->get_token();
    id_list.push_back(ident());
  }

  if (debugging)
    cout << "Parser: exiting ident_list" << endl;

  return id_list;
}*/

// <param_kind> ::= value 
//                | ref
lille_kind parser::param_kind()
{
  if (debugging)
    cout << "Parser: entering param_kind" << endl;

  lille_kind return_kind;

  if (scan->have(symbol::value_sym))
  {
    scan->get_token();
    return_kind = lille_kind::value_param;
  }
  else
  {
    scan->must_be(symbol::ref_sym);
    return_kind = lille_kind::ref_param;
  }

  if (id_tab->trace_all())
      cout << "Parser: param_kind() found: " << return_kind.to_string() << endl;

  if (debugging)
    cout << "Parser: exiting param_kind" << endl;

  return return_kind;
}

// <statement_list> ::= <statement> ; { <statement> ; }*
void parser::statement_list()
{
  if (debugging)
    cout << "Parser: entering statement_list" << endl;

  statement();
  scan->must_be(symbol::semicolon_sym);
  while(scan->have(symbol::identifier) or scan->have(symbol::exit_sym) or scan->have(symbol::return_sym) or scan->have(symbol::read_sym) or scan->have(symbol::write_sym) or scan->have(symbol::writeln_sym) or scan->have(symbol::null_sym) or scan->have(symbol::if_sym) or scan->have(symbol::while_sym) or scan->have(symbol::for_sym) or scan->have(symbol::loop_sym))
  {
    statement();
    scan->must_be(symbol::semicolon_sym);
  }

  if (debugging)
    cout << "Parser: exiting statement_list" << endl;
}

// <statement> ::= <simple_statement>
//               | <compound_statemen
void parser::statement()
{
  if (debugging)
    cout << "Parser: entering statement" << endl;

  if (scan->have(symbol::identifier) or scan->have(symbol::exit_sym) or scan->have(symbol::return_sym) or scan->have(symbol::read_sym) or scan->have(symbol::write_sym) or scan->have(symbol::writeln_sym) or scan->have(symbol::null_sym))
    simple_statement();
  else if (scan->have(symbol::if_sym) or scan->have(symbol::while_sym) or scan->have(symbol::for_sym) or scan->have(symbol::loop_sym))
    compound_statement();
  else
    error->flag(scan->this_token(), 80); // statement expected

  if (debugging)
    cout << "Parser: exiting statement" << endl;
}

// <simple_statement> ::= <ident> [ ( <expr> { , <expr> }* ) ]
//                      | <ident> := <expr>
//                      | exit [ when <expr> ]
//                      | return [ <expr> ]
//                      | read [ ( ] <ident> { , <ident> }* [ ) ]
//                      | write [ ( ] <expr> { , <expr> }* [ ) ]
//                      | writeln [ ( ] [ <expr> { , <expr> }* ] [ ) ]
//                      | null
void parser::simple_statement()
{
  if (debugging)
    cout << "Parser: entering simple_statement" << endl;

  bool open_paren = false; // tracks if there is an open parentheses, requires closing paren

  lille_type return_type;

  if (scan->have(symbol::identifier))
  {
    id_table_entry* id_info = ident(false); // gets the identifier from the id_table
    return_type = id_info->tipe(); // stores the type of the identifier
    if (scan->have(symbol::left_paren_sym))
    {
      scan->get_token(); // consume the left parentheses

      if (scan->have(symbol::right_paren_sym))
        error->flag(scan->this_token(), 138); // procedure or function call must have a parameter

      if (!(id_info->tipe().is_type(lille_type::type_proc) or id_info->tipe().is_type(lille_type::type_func)))
        error->flag(scan->this_token(), 90); // identifier must be a procedure or function name in this context
      
      return_type = id_info->return_tipe(); // return type updated to match the return type of the procedure or function

      int actual_param_count = 0; // tracks the number of actual parameters
      int formal_param_count = id_info->number_of_params(); // gets the number of parameters associated with this procedure or function
      
      // parses each actual parameter
      while (!scan->have(symbol::right_paren_sym))
      {
        if (id_tab->trace_all())
          cout << "Parser: simple_statement() call to a procedure or function" << endl;

        actual_param_count++; // increment the parameter count
        if (actual_param_count > formal_param_count)
        {
          error->flag(scan->this_token(), 100); // too many actual parameters
          while (!scan->have(symbol::right_paren_sym))
            scan->get_token();
          break;
        }

        lille_type param_type = expr();
        lille_type expected_param_type = id_info->nth_parameter(actual_param_count)->tipe();

        if (!param_type.is_equal(expected_param_type))
        {
          error->flag(scan->this_token(), 98); // Actual and formal parameter types do not match
          while (!scan->have(symbol::right_paren_sym))
            scan->get_token();
          break;
        }

        if (scan->have(symbol::comma_sym))
          scan->get_token();
        else
          break;
      }

      scan->must_be(symbol::right_paren_sym);

      if (actual_param_count < formal_param_count)
        error->flag(scan->this_token(), 97); // too few actual parameters
      }
      else if (scan->have(symbol::becomes_sym))
      {
        if (id_tab->trace_all())
          cout << "Parser: simple_statement() assignment" << endl;

        scan->get_token();

        if (!(id_info->kind().is_kind(lille_kind::variable) or (id_info->kind().is_kind(lille_kind::ref_param))))
          error->flag(scan->this_token(), 85); // identifier is not assignable, must be a variable or reference parameter

        if (scan->have(symbol::not_sym) or scan->have(symbol::odd_sym) or scan->have(symbol::left_paren_sym) or scan->have(symbol::identifier) or scan->have(symbol::integer) or scan->have(symbol::real_num) or scan->have(symbol::strng) or scan->have(symbol::true_sym) or scan->have(symbol::false_sym) or scan->have(symbol::plus_sym) or scan->have(symbol::minus_sym))
        {
          lille_type expr_type = expr();

          if (id_tab->trace_all())
          {
            cout << "Parser: simple_statement() id_info type: " << id_info->tipe().to_string() << endl;
            cout << "Parser: simple_statement() expr type: " << expr_type.to_string() << endl;
          }
          if (!id_info->tipe().is_equal(expr_type))
            error->flag(scan->this_token(), 93); // LHS and RHS are assignment are not compatible
        }
        else
          error->flag(scan->this_token(), 91); // Identifier illegal in this context

        /*if (!(id_info->kind().is_kind(lille_kind::variable) or (id_info->kind().is_kind(lille_kind::ref_param))))
        {
          //trace_write(id_info, true);
          cout << "trace write" << endl;
        }  
        else
          error->flag(scan->this_token(), 92); // String or expression expected*/
      }
  }
  else if (scan->have(symbol::exit_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: simple_statement() exit statement" << endl;

    scan->get_token();
    if(scan->have(symbol::when_sym))
    {
      scan->get_token();
      expr();
    }
  }
  else if (scan->have(symbol::return_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: simple_statement() return statement" << endl;

    scan->get_token();
    if (scan->have(symbol::not_sym) or scan->have(symbol::odd_sym) or scan->have(symbol::left_paren_sym) or scan->have(symbol::identifier) or scan->have(symbol::integer) or scan->have(symbol::real_num) or scan->have(symbol::strng) or scan->have(symbol::true_sym) or scan->have(symbol::false_sym) or scan->have(symbol::plus_sym) or scan->have(symbol::minus_sym))
      expr();
  }
  else if (scan->have(symbol::read_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: simple_statement() read statement" << endl;

    scan->get_token();
    if (scan->have(symbol::left_paren_sym))
    {
      scan->get_token();
      open_paren = true;
    }
    if(!scan->have(symbol::right_paren_sym))
    {
      id_table_entry* id = ident(false);
      if (id_tab->trace_all()) cout << "Parser: simple_statement() read:\n" << id->to_string() << endl;
      if (!(id->tipe().is_equal(lille_type::type_integer) or id->tipe().is_equal(lille_type::type_real)))
        error->flag(scan->this_token(), 131); // read statement can only read integer and real identifiers
      
      while(scan->have(symbol::comma_sym))
      {
        scan->get_token();
        id = ident(false);
        if (!(id->tipe().is_equal(lille_type::type_integer) or id->tipe().is_equal(lille_type::type_real)))
          error->flag(scan->this_token(), 131); // read statement can only read integer and real identifiers
      }
    }
    else
      error->flag(scan->this_token(), 137); // read statement must have an indentifier
    
    if (open_paren)
      scan->must_be(symbol::right_paren_sym);  
    else if (scan->have(symbol::right_paren_sym))
    {
      error->flag(scan->this_token(), 20); // missing left parenthese
      while (!scan->have(symbol::semicolon_sym))
        scan->get_token();
    }
  }
  else if (scan->have(symbol::write_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: simple_statement() write statement" << endl;

    scan->get_token();
    if (scan->have(symbol::left_paren_sym))
    {
      scan->get_token();
      open_paren = true;
    }

    if (!(scan->have(symbol::not_sym) or scan->have(symbol::odd_sym) or scan->have(symbol::left_paren_sym) or scan->have(symbol::identifier) or scan->have(symbol::integer) or scan->have(symbol::real_num) or scan->have(symbol::strng) or scan->have(symbol::true_sym) or scan->have(symbol::false_sym) or scan->have(symbol::plus_sym) or scan->have(symbol::minus_sym)))
      error->flag(scan->this_token(), 136); // write must have an expression argument
    
    lille_type expr_type = expr();

    if (!(expr_type.is_equal(lille_type::type_integer) or expr_type.is_equal(lille_type::type_real) or expr_type.is_equal(lille_type::type_string)))
      error->flag(scan->this_token(), 133); // write statement can only write integer, real or string values

    while(scan->have(symbol::comma_sym))
    {
      scan->get_token();
      expr_type = expr();

      if (!(expr_type.is_equal(lille_type::type_integer) or expr_type.is_equal(lille_type::type_real) or expr_type.is_equal(lille_type::type_string)))
        error->flag(scan->this_token(), 133); // write statement can only write integer, real or string values
    }
    if (open_paren)
      scan->must_be(symbol::right_paren_sym);  
    else if (scan->have(symbol::right_paren_sym))
    {
      error->flag(scan->this_token(), 20); // missing left parenthese
      while (!scan->have(symbol::semicolon_sym))
        scan->get_token();
    }
  }
  else if (scan->have(symbol::writeln_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: simple_statement() writeln statement" << endl;

    scan->get_token();
    if (scan->have(symbol::left_paren_sym))
    {
      scan->get_token();
      open_paren = true;
    }
    if (scan->have(symbol::not_sym) or scan->have(symbol::odd_sym) or scan->have(symbol::left_paren_sym) or scan->have(symbol::identifier) or scan->have(symbol::integer) or scan->have(symbol::real_num) or scan->have(symbol::strng) or scan->have(symbol::true_sym) or scan->have(symbol::false_sym) or scan->have(symbol::plus_sym) or scan->have(symbol::minus_sym))
    {
      lille_type expr_type = expr();

      if (!(expr_type.is_equal(lille_type::type_integer) or expr_type.is_equal(lille_type::type_real) or expr_type.is_equal(lille_type::type_string)))
        error->flag(scan->this_token(), 134); // writeln statement can only write integer, real or string values
      
      while(scan->have(symbol::comma_sym))
      {
        scan->get_token();
        expr_type = expr();
        
        if (!(expr_type.is_equal(lille_type::type_integer) or expr_type.is_equal(lille_type::type_real) or expr_type.is_equal(lille_type::type_string)))
          error->flag(scan->this_token(), 133); // write statement can only write integer, real or string values
      }
    }
    if (open_paren)
      scan->must_be(symbol::right_paren_sym);  
    else if (scan->have(symbol::right_paren_sym))
    {
      error->flag(scan->this_token(), 20); // missing left parenthese
      while (!scan->have(symbol::semicolon_sym))
        scan->get_token();
    }
  }
  else if (scan->have(symbol::null_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: simple_statement() null statement" << endl;
    scan->get_token();
  }
  else
    error->flag(scan->this_token(), 83); // simple statement expected

  if (debugging)
    cout << "Parser: exiting simple_statement" << endl;
}

// <compound_statement> ::= <if_statement>
//                        | <loop_statement>
//                        | <for_statement>
//                        | <while_statement
void parser::compound_statement()
{
  if (debugging)
    cout << "Parser: entering compound_statement" << endl;

  if (scan->have(symbol::if_sym))
    if_statement();
  else if (scan->have(symbol::loop_sym))
    loop_statement();
  else if (scan->have(symbol::for_sym))
    for_statement();
  else if (scan->have(symbol::while_sym))
    while_statement();
  else
    error->flag(scan->this_token(), 101); // compound statement expected

  if (debugging)
    cout << "Parser: exiting compound_statement" << endl;
}

// <if_statement> ::= if <expr> then <statement_list> { elsif <expr> then <statement_list> }* [ else <statement_list> ] end if
void parser::if_statement()
{
  if (debugging)
    cout << "Parser: entering if_statement" << endl;

  scan->must_be(symbol::if_sym);
  expr();
  scan->must_be(symbol::then_sym);

  id_tab->enter_scope();
  if (id_tab->trace_all())
      cout << "Parser: if_statement() enter if scope" << endl;

  statement_list();
  
  id_tab->exit_scope();
  if (id_tab->trace_all())
      cout << "Parser: if_statement() exit if scope" << endl;

  while (scan->have(symbol::elsif_sym))
  {
    scan->must_be(symbol::elsif_sym);
    expr();
    scan->must_be(symbol::then_sym);
    
    id_tab->enter_scope();
    if (id_tab->trace_all())
      cout << "Parser: if_statement() enter elsif scope" << endl;

    statement_list();
    
    id_tab->exit_scope();
    if (id_tab->trace_all())
      cout << "Parser: if_statement() exit elsif scope" << endl;
  }
  if (scan->have(symbol::else_sym))
  {
    scan->get_token();

    id_tab->enter_scope();
    if (id_tab->trace_all())
      cout << "Parser: if_statement() enter else scope" << endl;

    statement_list();
    
    id_tab->exit_scope();
    if (id_tab->trace_all())
      cout << "Parser: if_statement() exit else scope" << endl;
  }
  scan->must_be(symbol::end_sym);
  scan->must_be(symbol::if_sym);

  if (debugging)
    cout << "Parser: exiting if_statment" << endl;
}

// <while_statement> ::= while <expr> <loop_statement>
void parser::while_statement()
{
  if (debugging)
    cout << "Parser: entering while_statment" << endl;
  
  scan->must_be(symbol::while_sym);
  expr();

  id_tab->enter_scope();
  if (id_tab->trace_all())
    cout << "Parser: while_statement() enter while scope" << endl;

  loop_statement();
  
  id_tab->exit_scope();
  if (id_tab->trace_all())
    cout << "Parser: while_statement() exit while scope" << endl;

  if (debugging)
    cout << "Parser: exiting while_statement" << endl;
}

// <for_statement> ::= for <ident> in [ reverse ] <range> <loop_statement>
void parser::for_statement()
{
  if (debugging)
    cout << "Parser: entering for_statement" << endl;

  id_tab->enter_scope();
  if (id_tab->trace_all())
      cout << "Parser: for_statement() enter for scope" << endl;

  scan->must_be(symbol::for_sym);
  ident(true);
  scan->must_be(symbol::in_sym);
  if (scan->have(symbol::reverse_sym))
    scan->get_token();
  range();
  loop_statement();

  id_tab->exit_scope();
  if (id_tab->trace_all())
      cout << "Parser: for_statement() exit for scope" << endl;

  if (debugging)
    cout << "Parser: exiting for_statement" << endl;
}

// <loop_statement> ::= loop <statement_list> end loop
void parser::loop_statement()
{
  if (debugging)
    cout << "Parser: entering loop_statement" << endl;

  scan->must_be(symbol::loop_sym);
  statement_list();
  scan->must_be(symbol::end_sym);
  scan->must_be(symbol::loop_sym);

  if (debugging)
    cout << "Parser: exiting loop_statement" << endl;
}

// <range> ::= <simple_expr> .. <simple_expr>
lille_type parser::range()
{
  if (debugging)
    cout << "Parser: entering range" << endl;

  lille_type return_type;

  return_type = simple_expr();
  if (id_tab->trace_all()) cout << "Parser: range() first_return_type: " << return_type.to_string() << endl;

  scan->must_be(symbol::range_sym);

  lille_type second_return_type = simple_expr();
  if (id_tab->trace_all()) cout << "Parser: range() second_return_type: " << second_return_type.to_string() << endl;

    if (!return_type.is_equal(second_return_type))
    {
      error->flag(scan->this_token(), 114); // Types of expressions must match
      return_type = lille_type::type_unknown;
    }

  if (id_tab->trace_all())
      cout << "Parser: range() range type: " << return_type.to_string() << endl;

  if (debugging)
    cout << "Parser: exiting range" << endl;

  return return_type;
}

// <expr> ::= <simple_expr> [ <relop> <simple_expr> ]
//          | <simple_expr> in <range>
lille_type parser::expr()
{
  if (debugging)
    cout << "Parser: entering expr" << endl;

  lille_type return_type;

  return_type = simple_expr();

  if (scan->have(symbol::greater_than_sym) or scan->have(symbol::less_than_sym) or scan->have(symbol::equals_sym) or scan->have(symbol::not_equals_sym) or scan->have(symbol::reverse_sym) or scan->have(symbol::less_or_equal_sym) or scan->have(symbol::greater_or_equal_sym)) 
  {
    if (id_tab->trace_all())
      cout << "Parser: expr() relop" << endl;

    relop();
    lille_type second_return_type = simple_expr();

      if (!return_type.is_equal(second_return_type))
        error->flag(scan->this_token(), 114); // Types of expressions must match
  }
  else if (scan->have(symbol::in_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: expr() range" << endl;

    scan->get_token();
    lille_type second_return_type = range();

      if (!return_type.is_equal(second_return_type))
      error->flag(scan->this_token(), 114); // Types of expressions must match
  }
  
  if (debugging)
    cout << "Parser: exiting expr" << endl;

  return return_type;
}

//<bool> ::= true
//         | false
lille_type parser::boolean()
{
  if (debugging)
    cout << "Parser: entering boolean" << endl;

  if (scan->have(symbol::true_sym))
    scan->get_token();
  else 
    scan->must_be(symbol::false_sym);

  if (debugging)
    cout << "Parser: exiting boolean" << endl;

  return lille_type(lille_type::type_boolean);
}

// <relop> ::= > 
//           | < 
//           | = 
//           | <> 
//           | <= 
//           | >=
void parser::relop()
{
  if (debugging)
    cout << "Parser: entering relop" << endl;

  if (scan->have(symbol::greater_than_sym))
    scan->get_token();
  else if (scan->have(symbol::less_than_sym))
    scan->get_token();
  else if (scan->have(symbol::equals_sym))
    scan->get_token();
  else if (scan->have(symbol::not_equals_sym))
    scan->get_token();
  else if (scan->have(symbol::less_or_equal_sym))
    scan->get_token();
  else 
    scan->must_be(symbol::greater_or_equal_sym);

  if (debugging)
    cout << "Parser: exiting relop" << endl;
}

// <simple_expr> ::= <expr2> { <stringop> <expr2> }*
lille_type parser::simple_expr()
{
  if (debugging)
    cout << "Parser: entering simple_expr" << endl;
  
  lille_type return_type;

  return_type = expr2();
  while (scan->have(symbol::ampersand_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: simple_expr() string op" << endl;

    stringop();
    lille_type second_return_type = expr2();

      if (!return_type.is_equal(second_return_type))
      error->flag(scan->this_token(), 114); // Types of expressions must match
  }

  if (debugging)
    cout << "Parser: exiting simple_expr" << endl;

  return return_type;
}

// <stringop> ::= &
void parser::stringop()
{
  if (debugging)
    cout << "Parser: entering stringop" << endl;

  scan->must_be(symbol::ampersand_sym);

  if (debugging)
    cout << "Parser: exiting stringop" << endl;
}

// <expr2> ::= <term> { { <addop> | or } <term> }*
lille_type parser::expr2()
{
  if (debugging)
    cout << "Parser: entering expr2" << endl;

  lille_type return_type;
  
  return_type = term();
  while (scan->have(symbol::plus_sym) or scan->have(symbol::minus_sym) or scan->have(symbol::or_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: expr2() addop" << endl;

    if (scan->have(symbol::plus_sym) or scan->have(symbol::minus_sym))
      addop();
    else 
      scan->must_be(symbol::or_sym);
    lille_type second_return_type = term();
    
    if (!return_type.is_equal(second_return_type))
      if ((return_type.is_equal(lille_type::type_integer) and second_return_type.is_equal(lille_type::type_real)) or ((return_type.is_equal(lille_type::type_real) and second_return_type.is_equal(lille_type::type_integer))))
        return_type = lille_type::type_real; // expection for integer and real operations
      else
        error->flag(scan->this_token(), 114); // Types of expressions must match
  }

  if (debugging)
    cout << "Parser: exiting expr2" << endl;

  return return_type;
}

// <addop> ::= + | –
void parser::addop()
{
  if (debugging)
    cout << "Parser: entering addop" << endl;
  
  if (scan->have(symbol::plus_sym))
    scan->get_token();
  else 
    scan->must_be(symbol::minus_sym);

  if (debugging)
    cout << "Parser: exiting addop" << endl;
}

// <term> ::= <factor> { { <multop> | and } <factor> }*
lille_type parser::term()
{
  if (debugging)
    cout << "Parser: entering term" << endl;

  lille_type return_type;

  return_type = factor();
  while (scan->have(symbol::asterisk_sym) or scan->have(symbol::slash_sym) or scan->have(symbol::and_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: term() factor" << endl;

    if (scan->have(symbol::asterisk_sym) or scan->have(symbol::slash_sym))
      multop();
    else 
      scan->must_be(symbol::and_sym);
    lille_type second_return_type = factor();
    
    if (!return_type.is_equal(second_return_type))
      if ((return_type.is_equal(lille_type::type_integer) and second_return_type.is_equal(lille_type::type_real)) or ((return_type.is_equal(lille_type::type_real) and second_return_type.is_equal(lille_type::type_integer))))
        return_type = lille_type::type_real; // expection for integer and real operations
      else
        error->flag(scan->this_token(), 114); // Types of expressions must match
  }

  if (debugging)
    cout << "Parser: exiting term" << endl;

  return return_type;
}

// <multop> ::= * | /
void parser::multop()
{
  if (debugging)
    cout << "Parser: entering multop" << endl;

  if (scan->have(symbol::asterisk_sym))
    scan->get_token();
  else 
    scan->must_be(symbol::slash_sym);

  if (debugging)
    cout << "Parser: exiting multop" << endl;
}

//<factor> ::= <primary> [ ** <primary> ]
//            | [ <addop> ] <primary>
lille_type parser::factor()
{
  if (debugging)
    cout << "Parser: entering factor" << endl;
  
  lille_type return_type;

  if (scan->have(symbol::not_sym) or scan->have(symbol::odd_sym) or scan->have(symbol::left_paren_sym) or scan->have(symbol::identifier) or scan->have(symbol::integer) or scan->have(symbol::real_num) or scan->have(symbol::strng) or scan->have(symbol::true_sym) or scan->have(symbol::false_sym))
  {
    return_type = primary();
    if (scan->have(symbol::power_sym))
    {
      if (id_tab->trace_all())
        cout << "Parser: factor() exponent" << endl;

      scan->get_token();
      lille_type second_return_type = primary();

      if (!return_type.is_equal(second_return_type))
        error->flag(scan->this_token(), 130); // Flagging the error using the new error message for mismatched types in a power operation
    }
  }
  else if (scan->have(symbol::plus_sym) or scan->have(symbol::minus_sym))
  {
    addop();
    return_type = primary();
  }    

  if (debugging)
    cout << "Parser: exiting factor" << endl;

  return return_type;
}

// <primary> ::= not <expr>
//             | odd <expr>
//             | ( <simple_expr> )
//             | <ident> [ ( <expr>{ , <expr> }* ) ]
//             | <number>
//             | <string>
//             | <bool>
lille_type parser::primary()
{
  if (debugging)
    cout << "Parser: entering primary" << endl;
  
  lille_type return_type;

  // handle a not expression
  if (scan->have(symbol::not_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: primary() not" << endl;

    scan->get_token();
    return_type = expr();
  }

  // handle an odd expression
  else if (scan->have(symbol::odd_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: primary() odd" << endl;

    scan->get_token();
    return_type = expr();
  }

  // handle a simple expression
  else if (scan->have(symbol::left_paren_sym))
  {
    if (id_tab->trace_all())
      cout << "Parser: primary() simple expression" << endl;

    scan->get_token();
    return_type = simple_expr();
    scan->must_be(symbol::right_paren_sym);
  }

  // handle an identifier
  else if (scan->have(symbol::identifier))
  {
    if (id_tab->trace_all())
      cout << "Parser: primary() identifier" << endl;

    // handle the identifier token
    id_table_entry* id_info = ident(false);    
    return_type = id_info->tipe();

    // handle a procedure
    if (scan->have(symbol::left_paren_sym))
    {
      if (id_tab->trace_all())
      cout << "Parser: primary() procedure" << endl;
      // consume the left parenthese
      scan->get_token();

      // identifier must be a procedure or a function name in this context
      if (!(id_info->tipe().is_type(lille_type::type_proc) or id_info->tipe().is_type(lille_type::type_func)))
        error->flag(scan->this_token(), 132);
      
      // return type updated to match the return type of the procedure
      return_type = id_info->return_tipe();

      // track the number of parameters and the expected number
      int actual_param_count = 0;
      int formal_param_count = id_info->number_of_params();
      
      // handles each actual parameter
      while (!scan->have(symbol::right_paren_sym))
      {
        // increment the parameter count
        actual_param_count++;
        if (actual_param_count > formal_param_count)
        {
          error->flag(scan->this_token(), 100); // too many actual parameters
          while (!scan->have(symbol::right_paren_sym))
            scan->get_token();
          break;
        }
        // track the parameter type and expected parameter type
        lille_type param_type = expr();
        lille_type expected_param_type = id_info->nth_parameter(actual_param_count)->tipe();

        // actual and formal parameter types must match
        if (!param_type.is_equal(expected_param_type))
          error->flag(scan->this_token(), 98);

        // handles looping for multiple actual parameters
        if (scan->have(symbol::comma_sym))
          scan->get_token();
        else
          break;
      }
      // consume the right parenthese
      scan->must_be(symbol::right_paren_sym);

      // too few actual parameters
      if (actual_param_count < formal_param_count)
        error->flag(scan->this_token(), 97);
    }
  }

  // handle a number
  else if (scan->have(symbol::integer) or scan->have(symbol::real_num))
    return_type = number();

  // handle a string
  else if (scan->have(symbol::strng))
    return_type = string();

  // handle a boolean
  else if (scan->have(symbol::true_sym) or scan->have(symbol::false_sym))
    return_type = boolean();

  // primary must parse a factor
  else
    error->flag(scan->this_token(), 128); // factor expected

  if (debugging)
    cout << "Parser: exiting primary" << endl;

  return return_type;
}

// <string> ::= " { <character> }+ "
lille_type parser::string()
{
  if (debugging)
    cout << "Parser: entering string" << endl;

  lille_type return_type;

  scan->must_be(symbol::strng);
  return_type = lille_type(lille_type::type_string);

  if (debugging)
    cout << "Parser: exiting string" << endl;

  return return_type;
}

// <ident> ::= letter { [ _ ] <ident2> }*
id_table_entry* parser::ident(bool for_variable)
{
  if (debugging)
    cout << "Parser: entering ident" << endl;
  
  id_table_entry* id_info;

  token* tok = scan->this_token(); // store the identifier
  scan->must_be(symbol::identifier); // consume the identifier
  if (id_tab->trace_all())
  {
    cout << "Parser: ident() lookup this token: " << endl;
    tok->print_token();
  }
  
  id_info = id_tab->lookup(tok, for_variable); // find the identifier in the id_table
  if (id_tab->trace_all())
  {
    if (id_info != nullptr)
    {
      cout << "Parser: ident() id_info returned from lookup:" << endl;
      cout << id_info->to_string() << endl;
    }
    else
      cout << "Parser: ident() Identifier not found in the id_table" << endl;
  }

  if (debugging)
    cout << "Parser: exiting ident" << endl;

  return id_info;
}

// <number> ::= <digit_seq> [. <digit_seq> ] [ <exp> <addop> <digit_seq> ]
lille_type parser::number()
{
  if (debugging)
    cout << "Parser: entering number" << endl;
  
  lille_type return_type;
  
  if (scan->have(symbol::integer))
  {
    scan->get_token();
    return_type = lille_type(lille_type::type_integer);
  }
  else 
  {
    scan->must_be(symbol::real_num);
    return_type = lille_type(lille_type::type_real);
  }

  if (debugging)
    cout << "Parser: exiting number" << endl;
  
  return return_type; 
}

// Called to start parsing the program
lille_type parser::program()
{
  if (debugging)
    cout << "Parser: entering program" << endl;
  
  //int return_count = 0; // the number of returns found in the program
      
  lille_type return_type;
 
  token* predefined_func;
  token* argument;
  symbol* predefined_sym;
  id_table_entry* func_id;
  id_table_entry* param_id;

  // adding predefined functions to the id table
  predefined_sym = new symbol(symbol::identifier);
  predefined_func = new token(predefined_sym, 0, 0);
  predefined_func->set_identifier_value("INT2REAL");
  func_id = id_tab->enter_id(predefined_func, lille_type::type_func, lille_kind::unknown, 0, 0, lille_type::type_integer);
  
  argument = new token(predefined_sym, 0, 0);
  argument->set_identifier_value("__int2real_arg__");
  param_id = new id_table_entry(argument, lille_type::type_real, lille_kind::value_param, 0, 0, lille_type::type_unknown);
  func_id->add_param(param_id);

  predefined_sym = new symbol(symbol::identifier);
  predefined_func = new token(predefined_sym, 0, 0);
  predefined_func->set_identifier_value("REAL2INT");
  func_id = id_tab->enter_id(predefined_func, lille_type::type_func, lille_kind::unknown, 0, 0, lille_type::type_real);
  
  argument = new token(predefined_sym, 0, 0);
  argument->set_identifier_value("__real2int_arg__");
  param_id = new id_table_entry(argument, lille_type::type_integer, lille_kind::value_param, 0, 0, lille_type::type_unknown);
  func_id->add_param(param_id);
  
  predefined_sym = new symbol(symbol::identifier);
  predefined_func = new token(predefined_sym, 0, 0);
  predefined_func->set_identifier_value("INT2STRING");
  func_id = id_tab->enter_id(predefined_func, lille_type::type_func, lille_kind::unknown, 0, 0, lille_type::type_string);
  
  argument = new token(predefined_sym, 0, 0);
  argument->set_identifier_value("__int2string_arg__");
  param_id = new id_table_entry(argument, lille_type::type_integer, lille_kind::value_param, 0, 0, lille_type::type_unknown);
  func_id->add_param(param_id);
  
  predefined_sym = new symbol(symbol::identifier);
  predefined_func = new token(predefined_sym, 0, 0);
  predefined_func->set_identifier_value("REAL2STRING");
  func_id = id_tab->enter_id(predefined_func, lille_type::type_func, lille_kind::unknown, 0, 0, lille_type::type_string);
  
  argument = new token(predefined_sym, 0, 0);
  argument->set_identifier_value("__real2string_arg__");
  param_id = new id_table_entry(argument, lille_type::type_real, lille_kind::value_param, 0, 0, lille_type::type_unknown);
  func_id->add_param(param_id);

  scan->get_token();
  prog();
  
  scan->must_be(symbol::end_of_program);
  return_type = lille_type(lille_type::type_boolean);

  if (debugging)
    cout << "Parser: exiting program" << endl;

  return return_type;
}
