#/*
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
#include <limits>

#include "symbol.h"
#include "error_handler.h"
#include "token.h"
#include "scanner.h"
#include "lille_exception.h"
#include "parser.h"

using namespace std;

parser::parser(scanner* scan, error_handler* err)
{
    this->scan = scan;
    this->error = error;
}

void parser::prog() // <prog> ::= program <ident> is <block> ;
{
  if (debugging)
    cout << "Parser: entering prog" << endl;

  scan->must_be(symbol::program_sym);
  ident();
  scan->must_be(symbol::is_sym);
  block();
  scan->must_be(symbol::semicolon_sym);

  if (debugging)
    cout << "Parser: exiting prog" << endl;
}

// <block> ::= { <declaration> }* begin <statement_list> end [ <ident> ]
void parser::block()
{
  if (debugging)
    cout << "Parser: entering block" << endl;

  if (scan->have(symbol::identifier) or scan->have(symbol::procedure_sym) or scan->have(symbol::function_sym))
    while (scan->have(symbol::identifier) or scan->have(symbol::procedure_sym) or scan->have(symbol::function_sym))
      declaration();
  scan->must_be(symbol::begin_sym);
  statement_list();
  scan->must_be(symbol::end_sym);
  scan->have(symbol::identifier);

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
  
  if (scan->have(symbol::identifier))
  {
    ident_list();
    scan->must_be(symbol::colon_sym);
    scan->have(symbol::constant_sym);
    type();
    if (scan->have(symbol::becomes_sym))
      if (scan->have(symbol::integer) or scan->have(symbol::real_num))
        number();
      else if (scan->have(symbol::strng))
        string();
      else if (scan->have(symbol::boolean_sym))
        boolean();
      else
      {
        error->flag(scan->this_token(), ); // number string or boolean expected
        scan->get_token(); // move on
      }
    scan->must_be(symbol::semicolon_sym);
  }
  else if (scan->have(symbol::procedure_sym))
  {
    scan->must_be(symbol::procedure_sym);
    scan->must_be(symbol::identifier);
    if (scan->have(symbol::left_paren_sym))
    {
      scan->must_be(symbol::left_paren_sym);
      param_list();
      scan->must_be(symbol::right_paren_sym);
    }
    scan->must_be(symbol::is_sym);
    block();
    scan->must_be(symbol::semicolon_sym);
  }
  else if (scan->have(symbol::function_sym))
  {
    scan->must_be(symbol::function_sym);
    scan->must_be(symbol::identifier);
    if (scan->have(symbol::left_paren_sym))
    {
      scan->must_be(symbol::left_paren_sym);
      param_list();
      scan->must_be(symbol::right_paren_sym);
    }
    scan->must_be(symbol::return_sym);
    type();
    scan->must_be(symbol::is_sym);
    block();
    scan->must_be(symbol::semicolon_sym);
  }

  if (debugging)
    cout << "Parser: exiting declaration" << endl;
}

// <type> ::= integer 
//          | real 
//          | string 
//          | boolean
void parser::type() 
{
  if (debugging)
    cout << "Parser: entering type" << endl;

  if (scan->have(symbol::integer_sym))
    scan->must_be(symbol::integer_sym);
  else if (scan->have(symbol::real_sym))
    scan->must_be(symbol::real_sym);
  else if (scan->have(symbol::string_sym))
    scan->must_be(symbol::string_sym);
  else if (scan->have(symbol::boolean_sym))
    scan->must_be(symbol::boolean_sym);
  else
  {
    error->flag(scan->this_token(), 96); // type name expected
    scan->get_token(); // move on
  }
  

  if (debugging)
    cout << "Parser: exiting type" << endl;
}

// <param_list> ::= <param> { ; <param> }*
void parser::param_list()
{
  if (debugging)
    cout << "Parser: entering param_list" << endl;
  
  param();

  if(scan->have(symbol::semicolon_sym))
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
void parser::ident_list()
{
  if (debugging)
    cout << "Parser: entering ident_list" << endl;

  ident();
  if(scan->have(symbol::comma_sym))
    while(scan->have(symbol::comma_sym))
    {
      scan->must_be(symbol::comma_sym);
      ident();
    }

  if (debugging)
    cout << "Parser: exiting ident_list" << endl;
}

// <param_kind> ::= value 
//                | ref
void parser::param_kind()
{
  if (debugging)
    cout << "Parser: entering param_kind" << endl;

  if (scan->have(symbol::value_sym))
    scan->must_be(symbol::value_sym);
  else
    scan->must_be(symbol::ref_sym);

  if (debugging)
    cout << "Parser: exiting param_kind" << endl;
}

// <statement_list> ::= <statement> ; { <statement> ; }*
void parser::statement_list()
{
  if (debugging)
    cout << "Parser: entering statement_list" << endl;

  statement();
  scan->must_be(symbol::semicolon_sym);
  if(scan->have(symbol::identifier) or scan->have(symbol::exit_sym) or scan->have(symbol::return_sym) or scan->have(symbol::read_sym) or scan->have(symbol::write_sym) or scan->have(symbol::writeln_sym) or scan->have(symbol::null_sym) or scan->have(symbol::if_sym) or scan->have(symbol::while_sym) or scan->have(symbol::for_sym) or scan->have(symbol::loop_sym))
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

  if (scan->have(symbol::identifier))
  {
    ident();
    if (scan->have(symbol::left_paren_sym))
    {
      scan->must_be(symbol::left_paren_sym);
      expr();
      if (scan->have(symbol::comma_sym))
        while(scan->have(symbol::comma_sym))
        {
          scan->must_be(symbol::comma_sym);
          expr();
        }
      scan->must_be(symbol::right_paren_sym);
    }
    else
    {
      scan->must_be(symbol::becomes_sym);
      expr();
    }
  }
  else if (scan->have(symbol::exit_sym))
  {
    scan->must_be(symbol::exit_sym);
    if(scan->have(symbol::when_sym))
    {
      scan->must_be(symbol::when_sym);
      expr();
    }
  }
  else if (scan->have(symbol::return_sym))
  {
    scan->must_be(symbol::return_sym);
    if (scan->have(symbol::not_sym) or scan->have(symbol::odd_sym) or scan->have(symbol::left_paren_sym) or scan->have(symbol::identifier) or scan->have(symbol::integer) or scan->have(symbol::real_num) or scan->have(symbol::strng) or scan->have(symbol::boolean_sym))
      expr();
  }
  else if (scan->have(symbol::read_sym))
  {
    scan->must_be(symbol::read_sym);
    if (scan->have(symbol::left_paren_sym))
      scan->must_be(symbol::left_paren_sym);
    ident();
    if (scan->have(symbol::comma_sym))
        while(scan->have(symbol::comma_sym))
        {
          scan->must_be(symbol::comma_sym);
          ident();
        }
    if (scan->have(symbol::right_paren_sym))
      scan->must_be(symbol::right_paren_sym);
  }
  else if (scan->have(symbol::write_sym))
  {
    scan->must_be(symbol::write_sym);
    if (scan->have(symbol::left_paren_sym))
      scan->must_be(symbol::left_paren_sym);
    expr();
    if (scan->have(symbol::comma_sym))
        while(scan->have(symbol::comma_sym))
        {
          scan->must_be(symbol::comma_sym);
          expr();
        }
    if (scan->have(symbol::right_paren_sym))
      scan->must_be(symbol::right_paren_sym);
  }
  else if (scan->have(symbol::writeln_sym))
  {
    scan->must_be(symbol::writeln_sym);
    if (scan->have(symbol::left_paren_sym))
      scan->must_be(symbol::left_paren_sym);
    if (scan->have(symbol::not_sym) or scan->have(symbol::odd_sym) or scan->have(symbol::left_paren_sym) or scan->have(symbol::identifier) or scan->have(symbol::integer) or scan->have(symbol::real_num) or scan->have(symbol::strng) or scan->have(symbol::boolean_sym))
    {
      expr();
      if (scan->have(symbol::comma_sym))
        while(scan->have(symbol::comma_sym))
        {
          scan->must_be(symbol::comma_sym);
          ident();
        }
    }
    if (scan->have(symbol::right_paren_sym))
      scan->must_be(symbol::right_paren_sym);
  }
  else if (scan->have(symbol::null_sym))
    scan->must_be(symbol::null_sym);
  else
  {
    error->flag(scan->this_token(), 83); // simple statement expected
    scan->get_token();  // move on
  }

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
  {
    error->flag(scan->this_token(), 101); // compound statement expected
    scan->get_token();
  }

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
  statement_list();
  if (scan->have(symbol::elsif_sym))
    while (scan->have(symbol::elsif_sym))
    {
      scan->must_be(symbol::elsif_sym);
      expr();
      scan->must_be(symbol::then_sym);
      statement_list();
    }
  if (scan->have(symbol::else_sym))
  {
    scan->must_be(symbol::else_sym);
    statement_list();
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
  loop_statement();

  if (debugging)
    cout << "Parser: exiting while_statement" << endl;
}

// <for_statement> ::= for <ident> in [ reverse ] <range> <loop_statement>
void parser::for_statement()
{
  if (debugging)
    cout << "Parser: entering for_statement" << endl;

  scan->must_be(symbol::for_sym);
  ident();
  scan->must_be(symbol::in_sym);
  if (scan->have(symbol::reverse_sym))
    scan->must_be(symbol::reverse_sym);
  range();
  loop_statement();

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
void parser::range()
{
  if (debugging)
    cout << "Parser: entering range" << endl;

  simple_expr();
  scan->must_be(symbol::range_sym);
  simple_expr();

  if (debugging)
    cout << "Parser: exiting range" << endl;
}

// <expr> ::= <simple_expr> [ <relop> <simple_expr> ]
//          | <simple_expr> in <range>
void parser::expr()
{
  if (debugging)
    cout << "Parser: entering expr" << endl;

  simple_expr();
  if (scan->have(symbol::greater_than_sym) or scan->have(symbol::less_than_sym) or scan->have(symbol::equals_sym) or scan->have(symbol::not_equals_sym) or scan->have(symbol::less_or_equal_sym) or scan->have(symbol::greater_or_equal_sym)) 
  {
    relop();
    simple_expr();
  }
  else if (scan->have(symbol::in_sym))
  {
    scan->must_be(symbol::in_sym);
    range();
  }

  if (debugging)
    cout << "Parser: exiting expr" << endl;
}

//<bool> ::= true
//         | false
void parser::boolean()
{
  if (debugging)
    cout << "Parser: entering boolean" << endl;

  if (scan->have(symbol::true_sym))
    scan->must_be(symbol::true_sym);
  else if (scan->have(symbol::false_sym))
    scan->must_be(symbol::false_sym);
  else
  {
    error->flag(scan->this_token(), 103); // boolean expression expected
    scan->get_token();
  }

  if (debugging)
    cout << "Parser: exiting boolean" << endl;
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
    scan->must_be(symbol::greater_than_sym);
  else if (scan->have(symbol::less_than_sym))
    scan->must_be(symbol::less_than_sym);
  else if (scan->have(symbol::equals_sym))
    scan->must_be(symbol::equals_sym);
  else if (scan->have(symbol::not_equals_sym))
    scan->must_be(symbol::not_equals_sym);
  else if (scan->have(symbol::less_or_equal_sym))
    scan->must_be(symbol::less_or_equal_sym);
  else if (scan->have(symbol::greater_or_equal_sym))
    scan->must_be(symbol::greater_or_equal_sym);
  else 
  {
    error->flag(scan->this_token(), 105); // relop expected
    scan->get_token();                                     
  }

  if (debugging)
    cout << "Parser: exiting relop" << endl;
}

// <simple_expr> ::= <expr2> { <stringop> <expr2> }*
void parser::simple_expr()
{
  if (debugging)
    cout << "Parser: entering simple_expr" << endl;
  
  expr2();
  if (scan->have(symbol::ampersand_sym))
    while (scan->have(symbol::ampersand_sym))
    {
      stringop();
      expr2();
    }

  if (debugging)
    cout << "Parser: exiting simple_expr" << endl;
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
void parser::expr2()
{
  if (debugging)
    cout << "Parser: entering expr2" << endl;

  term();
  if (scan->have(symbol::plus_sym) or scan->have(symbol::minus_sym) or scan->have(symbol::or_sym))
    while (scan->have(symbol::plus_sym) or scan->have(symbol::minus_sym) or scan->have(symbol::or_sym))
    {
      if (scan->have(symbol::plus_sym) or scan->have(symbol::minus_sym))
        addop();
      else if (scan->have(symbol::or_sym))
        scan->must_be(symbol::or_sym);
      else
      {
        error->flag(scan->this_token(), 113); // illegal symbol follows expression
        scan->get_token(); // move on
      }
      term();
    }

  if (debugging)
    cout << "Parser: exiting expr2" << endl;
}

// <addop> ::= + | –
void parser::addop()
{
  if (debugging)
    cout << "Parser: entering addop" << endl;
  
  if (scan->have(symbol::plus_sym))
    scan->must_be(symbol::plus_sym);
  else if (scan->have(symbol::minus_sym))
    scan->must_be(symbol::minus_sym);
  else
  {
    error->flag(scan->this_token(), 125); // addop expected
    scan->get_token();
  }

  if (debugging)
    cout << "Parser: exiting addop" << endl;
}

// <term> ::= <factor> { { <multop> | and } <factor> }*
void parser::term()
{
  if (debugging)
    cout << "Parser: entering term" << endl;

  factor();
  if (scan->have(symbol::asterisk_sym) or scan->have(symbol::slash_sym) or scan->have(symbol::and_sym))
    while (scan->have(symbol::asterisk_sym) or scan->have(symbol::slash_sym) or scan->have(symbol::and_sym))
    {
      if (scan->have(symbol::asterisk_sym) or scan->have(symbol::slash_sym))
        multop();
      else if (scan->have(symbol::and_sym))
        scan->must_be(symbol::and_sym);
      else {
        error->flag(scan->this_token(), ); // multop or and expected
        scan->get_token();
      }
      factor();
    }

  if (debugging)
    cout << "Parser: exiting term" << endl;
}

// <multop> ::= * | /
void parser::multop()
{
  if (debugging)
    cout << "Parser: entering multop" << endl;

  if (scan->have(symbol::asterisk_sym))
    scan->must_be(symbol::asterisk_sym);
  else if (scan->have(symbol::slash_sym))
    scan->must_be(symbol::slash_sym);
  else
  {
    error->flag(scan->this_token(), 126); // multop expected
    scan->get_token();
  }

  if (debugging)
    cout << "Parser: exiting multop" << endl;
}

//<factor> ::= <primary> [ ** <primary> ]
//            | [ <addop> ] <primary>
void parser::factor()
{
  if (debugging)
    cout << "Parser: entering factor" << endl;
  
  if (scan->have(symbol::plus_sym) or scan->have(symbol::minus_sym))
    addop();
  primary();
  if (scan->have(symbol::power_sym))
  {
    scan->must_be(symbol::power_sym);
    primary();
  }

  if (debugging)
    cout << "Parser: exiting factor" << endl;
}

// <primary> ::= not <expr>
//             | odd <expr>
//             | ( <simple_expr> )
//             | <ident> [ ( <expr>{ , <expr> }* ) ]
//             | <number>
//             | <string>
//             | <bool>
void parser::primary()
{
  if (debugging)
    cout << "Parser: entering primary" << endl;

  if (scan->have(symbol::not_sym))
  {
    scan->must_be(symbol::not_sym);
    expr();
  }
  else if (scan->have(symbol::odd_sym))
  {
    scan->must_be(symbol::odd_sym);
    expr();
  }
  else if (scan->have(symbol::left_paren_sym))
  {
    scan->must_be(symbol::left_paren_sym);
    simple_expr();
    scan->must_be(symbol::right_paren_sym);
  }
  else if (scan->have(symbol::identifier))
  {
    scan->must_be(symbol::identifier);
    if (scan->have(symbol::left_paren_sym))
    {
      scan->must_be(symbol::left_paren_sym);
      expr();
      if (scan->have(symbol::comma_sym))
        while (scan->have(symbol::comma_sym))
        {
          scan->must_be(symbol::comma_sym);
          expr();
        }
      scan->must_be(symbol::right_paren_sym);
    }
  }
  else if (scan->have(symbol::integer) or scan->have(symbol::real_num))
    number();
  else if (scan->have(symbol::strng))
    string();
  else if (scan->have(symbol::boolean_sym))
    boolean();
  else
  {
    error->flag(scan->this_token(), 92); // String or expression expected
    scan->get_token();
  }

  if (debugging)
    cout << "Parser: exiting primary" << endl;
}

// <string> ::= " { <character> }+ "
void parser::string()
{
  if (debugging)
    cout << "Parser: entering string" << endl;

  scan->must_be(symbol::strng);

  if (debugging)
    cout << "Parser: exiting string" << endl;
}

// <ident> ::= letter { [ _ ] <ident2> }*
void parser::ident()
{
  if (debugging)
    cout << "Parser: entering ident" << endl;
  
  scan->must_be(symbol::identifier);
  
  if (debugging)
    cout << "Parser: exiting ident" << endl;
}

// <number> ::= <digit_seq> [. <digit_seq> ] [ <exp> <addop> <digit_seq> ]
void parser::number()
{
  if (debugging)
    cout << "Parser: entering number" << endl;

  if (scan->have(symbol::integer))
    scan->must_be(symbol::integer);
  else if (scan->have(symbol::real_num))
    scan->must_be(symbol::real_num);
  else
  {
    error->flag(scan->this_token(), 127); // A number is expected
    scan->get_token();
  }

  if (debugging)
    cout << "Parser: exiting number" << endl;
}

// Called to start parsing the  program
void parser::program()
{
  if (debugging)
    cout << "Parser: entering program" << endl;
  
  scan->get_token();
  prog();

  if (debugging)
    cout << "Parser: exitinging program" << endl;
}