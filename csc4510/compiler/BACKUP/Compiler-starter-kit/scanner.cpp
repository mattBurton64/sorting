/*
 * scanner.cpp
 *
 *  Created on: May 26, 2020
 *      Author: Michael Oudshoorn
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

using namespace std;


scanner::scanner()
{
	pos_on_line = -1;	// Nothing read from the input buffer yet.
	line_number = 0;
	eoln_flag = true;	// assume end of line is true before reading anything from the input buffer.
	eof_flag = false;
	input_buffer = "";
	next_char = end_marker;
	current_symbol = new symbol();
	current_token = new token();
	current_line_number = 0;
	current_pos_on_line = 0;
	current_integer_value = 0;
	current_real_value = 0.0;
	current_string_value = "";
	current_identifier_name = "";	
	error = NULL;		// specified by public constructor
	id_tab = NULL;		// specified by public constructor
  recovering = false; // initialize errpr recovery for the parser
}


scanner::scanner(string source_filename, id_table* id_t, error_handler* e) : scanner::scanner()
// Open source file. Raise exception if it is not present.
{
	id_tab = id_t;
	error = e;
	if (filesystem::exists(source_filename))		// Check file exists
		source_file.open(source_filename);          // Open default file for reading.
	else
	{
		cerr << "Source code file not found." << endl;
		throw lille_exception("Source code file not found.");
	}
	get_line();
}


int error_message(symbol::symbol_type s)
// Error message associated with symbol s in scanner. This is used so that we have consistency in the error message returned.
{
	switch (s) {
	case symbol::identifier:
		return 0;
		break;
	case symbol::strng:
		return 1;
		break;
	case symbol::real_num:
		return 2;
		break;
	case symbol::integer:
		return 3;
		break;
	case symbol::end_of_program:
		return 4;
		break;
	case symbol::semicolon_sym:
		return 5;
		break;
	case symbol::colon_sym:
		return 6;
		break;
	case symbol::comma_sym:
		return 7;
		break;
	case symbol::equals_sym:
		return 8;
		break;
	case symbol::not_equals_sym:
		return 9;
		break;
	case symbol::less_than_sym:
		return 10;
		break;
	case symbol::greater_than_sym:
		return 11;
		break;
	case symbol::less_or_equal_sym:
		return 12;
		break;
	case symbol::greater_or_equal_sym:
		return 13;
		break;
	case symbol::plus_sym:
		return 14;
		break;
	case symbol::minus_sym:
		return 15;
		break;
	case symbol::slash_sym:
		return 16;
		break;
	case symbol::asterisk_sym:
		return 17;
		break;
	case symbol::power_sym:
		return 18;
		break;
	case symbol::ampersand_sym:
		return 19;
		break;
	case symbol::left_paren_sym:
		return 20;
		break;
	case symbol::right_paren_sym:
		return 21;
		break;
	case symbol::range_sym:
		return 22;
		break;
	case symbol::becomes_sym:
		return 23;
		break;
	case symbol::and_sym:
		return 24;
		break;
	case symbol::begin_sym:
		return 25;
		break;
	case symbol::boolean_sym:
		return 26;
		break;
	case symbol::constant_sym:
		return 27;
		break;
	case symbol::else_sym:
		return 28;
		break;
	case symbol::elsif_sym:
		return 29;
		break;
	case symbol::end_sym:
		return 30;
		break;
	case symbol::eof_sym:
		return 31;
		break;
	case symbol::exit_sym:
		return 32;
		break;
	case symbol::false_sym:
		return 33;
		break;
	case symbol::for_sym:
		return 34;
		break;
	case symbol::function_sym:
		return 35;
		break;
	case symbol::if_sym:
		return 36;
		break;
	case symbol::in_sym:
		return 37;
		break;
	case symbol::integer_sym:
		return 38;
		break;
	case symbol::is_sym:
		return 39;
		break;
	case symbol::loop_sym:
		return 40;
		break;
	case symbol::not_sym:
		return 41;
		break;
	case symbol::null_sym:
		return 42;
		break;
	case symbol::odd_sym:
		return 43;
		break;
	case symbol::or_sym:
		return 44;
		break;
	case symbol::pragma_sym:
		return 45;
		break;
	case symbol::procedure_sym:
		return 46;
		break;
	case symbol::program_sym:
		return 47;
		break;
	case symbol::read_sym:
		return 48;
		break;
	case symbol::real_sym:
		return 49;
		break;
	case symbol::ref_sym:
		return 50;
		break;
	case symbol::return_sym:
		return 51;
		break;
	case symbol::reverse_sym:
		return 52;
		break;
	case symbol::string_sym:
		return 53;
		break;
	case symbol::then_sym:
		return 54;
		break;
	case symbol::true_sym:
		return 55;
		break;
	case symbol::value_sym:
		return 56;
		break;
	case symbol::when_sym:
		return 57;
		break;
	case symbol::while_sym:
		return 58;
		break;
	case symbol::write_sym:
		return 59;
		break;
	case symbol::writeln_sym:
		return 60;
		break;
	default:
		throw lille_exception("Unexpected symbol passed to Error_Message inside Scanner.");
		break;
	}
}


void scanner::get_char()
{
	// gets the next character from the input stream. Checks for end of line and end of file.

	if ((pos_on_line + 1) < input_buffer.length())
	{
		pos_on_line++;
		next_char = input_buffer.at(pos_on_line);
		eoln_flag = false;
	}
	else
		fill_buffer();
}


char scanner::following_char()
{
	// return the character after next_char;
	//if (pos_on_line < (input_buffer.length()-1))
	if ((!eof_flag) and ((pos_on_line + 1) < input_buffer.length()))
		return input_buffer.at(pos_on_line + 1);
	else
		return end_marker;;
}


void scanner::get_line()
{
	if (!source_file.eof())
	{
		getline(source_file, input_buffer);
		line_number++;
	}
	else
	{
		eof_flag = true;
		input_buffer = "";
	}

	if (debugging)
	{
		cout << "In GET_LINE " << line_number << ":  >" << input_buffer << "<" << endl;
	}
}


void scanner::fill_buffer()
// Routine to fill the buffer, i.e., read a line from the source file.
{
	pos_on_line = -1;
	get_line();
	eoln_flag = true;			// indicates end of previous line was encountered. Acts as a token delimiter.
	next_char = end_marker;
}



token* scanner::get_token()
// Get the current token from the input stream. It is held in the private variable current_token.
{
	//skip whitespace and comments to find start of next token.
	while ((!eof_flag) and ((next_char <= ' ') or ((next_char == '-') and (following_char() == '-'))))
	{
		// skip whitespace
		while ((!eof_flag) and (next_char <= ' '))
		{
			get_char();
		}

		// skip comments
		while ((!eof_flag) and ((next_char == '-') and (following_char() == '-')))
			fill_buffer();	// discard the rest of the line
	}

	// initialize variables to record token identified and its current location in the source file;
	current_symbol = new symbol(symbol::end_of_program);	// This is the token returned if at end of file.

	current_line_number = line_number;
	current_pos_on_line = pos_on_line;


	if (!eof_flag)	// If not at end of file
	{
		if (isalpha(next_char))
			scan_alpha();
		else if (isdigit(next_char))
			scan_digit();
		else
			scan_special_symbol();

		switch (current_symbol->get_sym())
		{
		case symbol::identifier:
			current_token = new token(new symbol(symbol::identifier), current_line_number, current_pos_on_line);
			current_token->set_identifier_value(current_identifier_name);
			break;
		case symbol::strng:
			current_token = new token(new symbol(symbol::strng), current_line_number, current_pos_on_line);
			current_token->set_string_value(current_string_value);
			break;
		case symbol::integer:
			current_token = new token(new symbol(symbol::integer), current_line_number, current_pos_on_line);
			current_token->set_integer_value(current_integer_value);
			break;
		case symbol::real_num:
			current_token = new token(new symbol(symbol::real_num), current_line_number, current_pos_on_line);
			current_token->set_real_value(current_real_value);
			break;
		case symbol::pragma_sym:		// pragmas are handled by the scanner not the parser
			parse_pragma();				// pragma can appear anywhere in the code.
			break;
		default:
			current_token = new token(current_symbol, current_line_number, current_pos_on_line);
		}
	}
	else
	{
		// At eof. Set token to end_of_program to indicate end of input.
		current_token = new token(new symbol(symbol::end_of_program), line_number, pos_on_line);
			// This is the token returned if at end of file.
			// The parser needs to process this to make sure that
			// there is no extraneous text after the end of the
			// code is processed.
	}

	if (debugging)
	{
		// display the token about to be returned.
		cout << "GET_TOKEN about to return... ";
		current_token->print_token();
	}

	return current_token;
}


void scanner::scan_string()
{
    	// Process a string. Need to ensure that a string begins and ends with a
    	// double quote and that the string is wholly contained on a single line in
    	// the source file. 2 adjacent double quote marks are interpreted as a single
    	// double quote character within the string.
    
    	// TO BE COMPLETED BEFORE THE SCANNER FUNCTIONS PROPERLY AND THE
    	// PARSER CAN BE STARTED.

	// INSERT CODE HERE.
  if (debugging)
    cout << "Scanner: executing scan_string" << endl;

  current_string_value = ""; // Initialize the string value

  get_char(); // Consume the opening double quote

  while (!eoln_flag and !eof_flag)
  { 
    if (next_char == '"')
    {
      if (following_char() == '"') // Checks for two double quotes, which should be treated as a single double quote character.
      {
         current_string_value += '"';
         get_char(); // Consume the first double quote
         get_char(); // Consume the second double quote
      }
      else // If the character following a double quote is not another double quote, end the string
      {
        if (debugging)
          cout << "Scanner: exiting scan_string (valid string)" << endl;

        if (current_string_value.length() == 0)
          error->flag(current_line_number, current_pos_on_line, 124); // Empty strings are not permitted

        // Handle the properly terminated string
        current_symbol = new symbol(symbol::strng);
        current_token = new token(current_symbol, current_line_number, current_pos_on_line);
        current_token->set_string_value(current_string_value);
        return;
      }
    } 
    else // If the next character in the string is not a double quote, append it to the current string
    {
      current_string_value += next_char;
      get_char();
    }
  }
  
  if (eoln_flag or eof_flag)
  {
    if (debugging)
      cout << "Scanner: exiting scan_string (eoln)" << endl;
    current_symbol = new symbol(symbol::strng);
    current_token = new token(current_symbol, current_line_number, current_pos_on_line);
    current_token->set_string_value(current_string_value);
    error->flag(current_line_number, current_pos_on_line, 60); // Unterminated string
    return;
  }
}


void scanner::scan_alpha()
{
	// Scan in a token beginning with a letter
	// *** TO BE COMPLETED ***
	// This method takes care of reserved words and identifies in the language. These begin with a alphabetic character
	// and contain an unlimited number of significant characters. Note that lower case letters are converted to upper case
	// before being stored. For each identifier, a check is made to see if the identifier maps onto a reserved word.
	// Make sure that there are no trailing underscores

	bool malformed_ident {false};
	current_identifier_name = "";

	current_identifier_name += char(toupper(next_char)); 	// in case it is an identifier, we need to record what the identifier actually is.
	get_char();
	while (isalpha(next_char) or isdigit(next_char) or (next_char == '_'))
	{
		if ((next_char == '_') and (following_char() == '_'))
			malformed_ident = true;
		current_identifier_name += char(toupper(next_char));
		get_char();
	}
	if (malformed_ident or (current_identifier_name.at(current_identifier_name.length() - 1)) == '_')
		error->flag(current_line_number, current_pos_on_line, 61); 		// Illegal underscore in identifier.
	// check to see if the string matches an a reserved word
	if (current_identifier_name == "AND")
		current_symbol = new symbol(symbol::and_sym);
	else if (current_identifier_name == "BEGIN")
		current_symbol = new symbol(symbol::begin_sym);
	else if (current_identifier_name == "BOOLEAN")
		current_symbol = new symbol(symbol::boolean_sym);
	else if (current_identifier_name == "CONSTANT")
		current_symbol = new symbol(symbol::constant_sym);
	else if (current_identifier_name == "ELSE")
		current_symbol = new symbol(symbol::else_sym);
	else if (current_identifier_name == "ELSIF")
		current_symbol = new symbol(symbol::elsif_sym);
	else if (current_identifier_name == "END")
		current_symbol = new symbol(symbol::end_sym);
	else if (current_identifier_name == "EOF")
		current_symbol = new symbol(symbol::eof_sym);
	else if (current_identifier_name == "EXIT")
		current_symbol = new symbol(symbol::exit_sym);
	else if (current_identifier_name == "FALSE")
		current_symbol = new symbol(symbol::false_sym);
	else if (current_identifier_name == "FOR")
		current_symbol = new symbol(symbol::for_sym);
	else if (current_identifier_name == "FUNCTION")
		current_symbol = new symbol(symbol::function_sym);
	else if (current_identifier_name == "IF")
		current_symbol = new symbol(symbol::if_sym);
	else if (current_identifier_name == "IN")
		current_symbol = new symbol(symbol::in_sym);
	else if (current_identifier_name == "INTEGER")
		current_symbol = new symbol(symbol::integer_sym);
	else if (current_identifier_name == "IS")
		current_symbol = new symbol(symbol::is_sym);
	else if (current_identifier_name == "LOOP")
		current_symbol = new symbol(symbol::loop_sym);
	else if (current_identifier_name == "NOT")
		current_symbol = new symbol(symbol::not_sym);
	else if (current_identifier_name == "NULL")
		current_symbol = new symbol(symbol::null_sym);
	else if (current_identifier_name == "ODD")
		current_symbol = new symbol(symbol::odd_sym);
	else if (current_identifier_name == "OR")
		current_symbol = new symbol(symbol::or_sym);
	else if (current_identifier_name == "PRAGMA")
		current_symbol = new symbol(symbol::pragma_sym);
	else if (current_identifier_name == "PROCEDURE")
		current_symbol = new symbol(symbol::procedure_sym);
	else if (current_identifier_name == "PROGRAM")
		current_symbol = new symbol(symbol::program_sym);
	else if (current_identifier_name == "READ")
		current_symbol = new symbol(symbol::read_sym);
	else if (current_identifier_name == "REAL")
		current_symbol = new symbol(symbol::real_sym);
	else if (current_identifier_name == "REF")
		current_symbol = new symbol(symbol::ref_sym);
	else if (current_identifier_name == "RETURN")
		current_symbol = new symbol(symbol::return_sym);
	else if (current_identifier_name == "REVERSE")
		current_symbol = new symbol(symbol::reverse_sym);
	else if (current_identifier_name == "STRING")
		current_symbol = new symbol(symbol::string_sym);
	else if (current_identifier_name == "THEN")
		current_symbol = new symbol(symbol::then_sym);
	else if (current_identifier_name == "TRUE")
		current_symbol = new symbol(symbol::true_sym);
	else if (current_identifier_name == "VALUE")
		current_symbol = new symbol(symbol::value_sym);
	else if (current_identifier_name == "WHEN")
		current_symbol = new symbol(symbol::when_sym);
	else if (current_identifier_name == "WRITE")
		current_symbol = new symbol(symbol::write_sym);
	else if (current_identifier_name == "WRITELN")
		current_symbol = new symbol(symbol::writeln_sym);
	else if (current_identifier_name == "WHILE")
		current_symbol = new symbol(symbol::while_sym);
	else
		current_symbol = new symbol(symbol::identifier);
}

void scanner::scan_digit()
{
	// scan in a token beginning with a digit
	// Note that a unary operator such as -1 would be detected as a minus sign followed by a digit.

    	// TO BE COMPLETED BEFORE THE SCANNER FUNCTIONS PROPERLY AND THE
    	// PARSER CAN BE STARTED.

	// INSERT CODE HERE.
  if (debugging)
    cout << "Scanner: executing scan_digit" << endl;

  int number_of_digits = 0; // Initialize the number of digits
  const int INT_MAX_DIGITS = numeric_limits<int>::digits10; // The maximum number of digits for an integer
  const int REAL_MAX_DIGITS = numeric_limits<double>::max_digits10; // The maximum number of digits for a real number
  const int EXPONENT_MAX_DIGITS = 3; // The maximum number of digits for an exponenet 

  bool is_real = false; // Tracks whether the number is real
  bool is_scientific = false; // Tracks whether the number is in sceintific notation
  bool is_negative = false; // Tracks whether the exponent is negative

  current_integer_value = 0; // Initialize the integer value
  current_real_value = 0.0; // Initialize the real value
  double current_scientific_value = 0; // Initialize the scientific factor
  
  string preceeding_decimal = ""; // Stores digits before the decimal
  string trailing_decimal = ""; // Stores digits after the decimal 
  string exponent = ""; // Stores digits in the exponent
  
  while (!eoln_flag and !eof_flag)
  {
    if (next_char == '.')
    {
      if (following_char() == '.') // range symbol check
      {
        if (is_real) 
          error->flag(current_line_number, current_pos_on_line, 104); // Ranges only permitted for integers
        break;
      }
      else if (is_scientific) // Throw an error for decimals in the exponents
      {
        error->flag(current_line_number, current_pos_on_line, 74); // Illegal character in exponent (decimal)
        break;
      }
      else if (isdigit(following_char()) and !is_real) // Start a real number
      {
        is_real = true; // make this a real number
        number_of_digits = 0; // reset digit counter
        get_char(); // consume the decimal
      }
      else // Throw an error when a decimal is followed by anything other than a number and isnt the range symbol
      {
        //  Handle returning tokens
        if (is_real) // Return a real number
        {
          current_symbol = new symbol(symbol::real_num);
          current_token = new token(current_symbol, current_line_number, current_pos_on_line);
            
          // Handle the base real number
          long long concatenated_real = stoll(preceeding_decimal + trailing_decimal); // temprorarilty store the combined digits in a long long because the decimal digits can exceed the integer max
          current_real_value = concatenated_real / pow(10.0, trailing_decimal.length()); // divide to shift the decimal

          if (is_scientific) // Handle the exponent
          {
            current_scientific_value = pow(10, stoi(exponent)); // convert the exponent to scientific value
            current_real_value *= current_scientific_value; // Apply the scientific value to the base
          }

          current_token->set_real_value(current_real_value);
        }
        else // Return an integer
        {
          current_symbol = new symbol(symbol::integer);
          current_token = new token(current_symbol, current_line_number, current_pos_on_line);
            
          current_integer_value = stoi(preceeding_decimal); // Convert the integer value

          if (is_scientific)
          {
            current_scientific_value = pow(10, stoi(exponent)); // convert the exponent to scientific value
            current_integer_value *= current_scientific_value; // Apply the scientific value to the base 
          }
            
          current_token->set_integer_value(current_integer_value);
        }   

        error->flag(current_line_number, current_pos_on_line, 63); // Real number must have digits after decimal
        return;
      }
    } 
    else if (next_char == 'e' or next_char == 'E' and !is_scientific) // Start an exponent
    {
      if (isdigit(following_char()) or following_char() == '+' or following_char() == '-')
      {
        is_scientific = true; // new digits will be appended to the exponent
        number_of_digits = 0; // reset digit count
        get_char(); // consume the e/E symbol
      }
      else
      {
        error->flag(current_line_number, current_pos_on_line, 64); // Must have digits after an exponent symbol 
        break;
      }
    }
    else if ((next_char == '+' or next_char == '-') and is_scientific) // Handle +/- in the exponent
    {
      if (exponent != "") // If there is a + or - symbol in the middle of an exponent terminate scanning the number
      {
        if (debugging)
          cout << "Scanner: scan_digit (exponent not empty)" << endl;
        break;
      }
      else if (next_char == '-') // Handle minus symbols
      {
        if (debugging)
          cout << "Scanner: scan_digit (minus symbol in exponent)" << endl;
        
        if (!isdigit(following_char())) // Require digits after minus symbol 
        {
          is_scientific = false; // prevent token from trying to apply an invalid exponent
          error->flag(current_line_number, current_pos_on_line, 64); // Must have digits after an exponent symbol 
          break;
        }
        else if (is_real)
          exponent += next_char;
        else
        {
          is_scientific = false; // prevent token from trying to apply an invalid exponent
          error->flag(current_line_number, current_pos_on_line, 67); // Integers must have a positive exponent
          break;
        }
      }
      get_char(); // Consume the + or - symbol       
    }
    else if (isdigit(next_char)) // handles appending new digits
    {
      if (is_scientific) // Handle exponents
      {
        if (number_of_digits + 1 > EXPONENT_MAX_DIGITS) // Throw an error for too many digits in the exponent
        {
          error->flag(current_line_number, current_pos_on_line, 65);
          break;
        }
        exponent += next_char; // append digit to exponent
      }
      else // Handle bases
      {
        if (is_real) // Handle reals
        {
          if (number_of_digits + 1 > REAL_MAX_DIGITS) // Prevent adding another digit that makes the number too large
          {
            error->flag(current_line_number, current_pos_on_line, 62); // Number too large 
            break;
          } 
          trailing_decimal += next_char; // append digit to the right of the decimal
        }
        else // Handle integers
        {
          if (number_of_digits + 1 > INT_MAX_DIGITS) // Prevent adding a digit that makes the int to large
          {
            error->flag(current_line_number, current_pos_on_line, 68); // Integer number too large or malformed
            break;
          }
          preceeding_decimal += next_char; // append digit to  the left of the decimal
        }
      }

      number_of_digits++; // Increase the digit counter
      get_char(); // Consume the digit
    }
    else // terminate scanning the number
    {
      if (debugging)
        cout << "Scanner: scan_digit (valid number)" << endl;
      
      break;
    }
  }

  //  Handle returning tokens
  if (is_real) // Return a real number
  { 
    current_symbol = new symbol(symbol::real_num);
    current_token = new token(current_symbol, current_line_number, current_pos_on_line);
   
    // Handle the base real number
    long long concatenated_real = stoll(preceeding_decimal + trailing_decimal); // temprorarilty store the combined digits in a long long because the decimal digits can exceed the integer max
    current_real_value = concatenated_real / pow(10.0, trailing_decimal.length()); // divide to shift the decimal
    
    if (is_scientific) // Handle the exponent
    {
      current_scientific_value = pow(10.0, stoi(exponent)); // convert the exponent to scientific value
      current_real_value *= current_scientific_value; // Apply the scientific value to the base
    }

    current_token->set_real_value(current_real_value);
  }
  else // Return an integer
  {
    current_symbol = new symbol(symbol::integer);
    current_token = new token(current_symbol, current_line_number, current_pos_on_line);
    
    current_integer_value = stoi(preceeding_decimal); // Convert the integer value

    if (is_scientific)
    {
      current_scientific_value = pow(10, stoi(exponent)); // convert the exponent to scientific value
      current_integer_value *= current_scientific_value; // Apply the scientific value to the base 
    }
    
    current_token->set_integer_value(current_integer_value);
  }

  if (debugging)
    cout << "Scanner: exiting scan_digit" << endl;
  
  return;
}

void scanner::scan_special_symbol()
{
// scan in a token beginning with a special character
	switch (next_char)		// handle multiple character tokens first, the single character tokens
	{
	case ':':	// BECOMES or a COLON
		if (following_char() == '=')
		{
			current_symbol = new symbol(symbol::becomes_sym);
			get_char();
		}
		else
			current_symbol = new symbol(symbol::colon_sym);
		break;
	case '<':	// LESS THAN, LESS OR EQUAL, or NOT EQUAL
		if (following_char() == '=')
		{
			current_symbol = new symbol(symbol::less_or_equal_sym);
			get_char();
		}
		else if (following_char() == '>')
		{
			current_symbol = new symbol(symbol::not_equals_sym);
			get_char();
		}
		else
			current_symbol = new symbol(symbol::less_than_sym);
		break;
	case '>':	// GREATER THAN, or GREATER OR EQUAL
		if (following_char() == '=')
		{
			current_symbol = new symbol(symbol::greater_or_equal_sym);
			get_char();
		}
		else
			current_symbol = new symbol(symbol::greater_than_sym);
		break;
	case '*':	// ASTERISK or POWER symbol
		if (following_char() == '*')
		{
			current_symbol = new symbol(symbol::power_sym);
			get_char();
		}
		else
			current_symbol = new symbol(symbol::asterisk_sym);
		break;
	case '.':	// RANGE symbol
		if (following_char() == '.')
		{
			current_symbol = new symbol(symbol::range_sym);
			get_char();
		}
		else
		{
			// illegal symbol
			current_symbol = new symbol(symbol::nul);
			error->flag(current_line_number, current_pos_on_line, 22);	// Expected a range token.
		}
		break;
	case '"':	// Start of a string
		scan_string();
		break;
	case '&':
		current_symbol = new symbol(symbol::ampersand_sym);
		break;
	case '/':
		current_symbol = new symbol(symbol::slash_sym);
		break;
	case ';':
		current_symbol = new symbol(symbol::semicolon_sym);
		break;
	case '(':
		current_symbol = new symbol(symbol::left_paren_sym);
		break;
	case ')':
		current_symbol = new symbol(symbol::right_paren_sym);
		break;
	case ',':
		current_symbol = new symbol(symbol::comma_sym);
		break;
	case '+':
		current_symbol = new symbol(symbol::plus_sym);
		break;
	case '-':
		current_symbol = new symbol(symbol::minus_sym);
		break;
	case '=':
		current_symbol = new symbol(symbol::equals_sym);
		break;
	default:
		current_symbol = new symbol(symbol::nul);
		error->flag(current_line_number, current_pos_on_line, 74); 	// illegal character.
		break;
	}
	get_char();	// get the next character

}


void scanner::parse_pragma()
{
// parse the pragma identified by the scanner.

    
    // NOTE. YOU WILL NEED TO RETURN TO THIS CODE ONCE THE PARSER AND SYMBOL TABLE
    // ARE WRITTEN IN ORDER TO IMPLEMENT THE FUNCTIONALITY OF PRAGMAS.
    
	string pragma_name = "";

	get_token();	// consume the pragma keyword
	if (current_symbol->get_sym() == symbol::identifier)
	{
		pragma_name = current_identifier_name;;
		if ((pragma_name != "ERROR_LIMIT")
				and (pragma_name != "TRACE")
				and (pragma_name != "UNTRACE")
				and (pragma_name != "DEBUG"))
			error->flag(current_line_number, current_pos_on_line, 70);		// Illegal pragma name
	}
	else
		error->flag(current_line_number, current_pos_on_line, 69);  	// Malformed pragma.
	get_token();	// consume pragma name
	// check to see if arguments are provided to the pragma
	if (current_symbol->get_sym() == symbol::left_paren_sym)
		get_token();	// consume left paren
		// C++ does not support the use of a switch statement on strings.
	else
		error->flag(current_line_number, current_pos_on_line, 20);	// pragmas have arguments so a left paren is expected.

	if (pragma_name == "ERROR_LIMIT")
	{
		if (current_symbol->get_sym() == symbol::integer)
        {
			// INSERT CODE HERE
        }
		else
			error->flag(current_line_number, current_pos_on_line, 71);	// pragma ERROR_LIMIT requires a numeric argument.
	}
	else if (pragma_name == "TRACE")
	{
		if (current_symbol->get_sym() == symbol::identifier)
			// Turn on tracing flag in the symbol table for this identifier.
			// Do not generate an error if the identifier is not present!
		{
            // INSERT CODE HERE
		}
		else
			error->flag(current_line_number, current_pos_on_line, 72);	// pragma TRACE requires a variable name.
	}
	else if (pragma_name == "UNTRACE")
	{
		if (current_symbol->get_sym() == symbol::identifier)
            // Turn off tracing flag in the symbol table for this identifier.
            // Do not generate an error if the identifier is not present!
        {
            // INSERT CODE HERE
        }
		else
			error->flag(current_line_number, current_pos_on_line, 72);	// pragma UNTRACE requires a variable name.
	}
	else if (pragma_name == "DEBUG")
	{
		if (current_symbol->get_sym() == symbol::identifier)
		{
			// INSERT CODE HERE
            // pragma DEBUG requires either ON or OFF as the argument.
		}
		else
			error->flag(current_line_number, current_pos_on_line, 72);	// pragma TRACE requires a variable name.
	}
	else
	{
		// Already generated an error message about an illegal pragma name
	}
	get_token();	// consume the argument
	if (current_symbol->get_sym() == symbol:: right_paren_sym)
		get_token();		// consume right paren
	else
		error->flag(current_line_number, current_pos_on_line, 21);	// Right paren expected
	if (current_symbol->get_sym() == symbol::semicolon_sym)
			get_token();		// consume semicolon
	else
		error->flag(current_line_number, current_pos_on_line, 5);	// semicolon expected

}



bool scanner::have(symbol::symbol_type s)
// Returns true if the current token is an s symbol, false otherwise.
{
	if (current_token->get_sym() == s)
		return true;
	else
		return false;
}


void scanner::must_be(symbol::symbol_type s)
// The current token must be an s symbol otherwise it is a syntax error. If the current token matches
// the symbol s, then the scanner discards the token and advances to the next token in the source file.
{
  if (recovering)
  {
    while (current_token->get_sym() != s and current_token->get_sym() != symbol::end_of_program)
	    get_token();
    if (current_token->get_sym() == s)
		  get_token();
    recovering = false;
  }
	else if (current_token->get_sym() == s)
    get_token();
	else 
  {
    error->flag(current_token, error_message(s));
    recovering = true;
  }
}

token* scanner::this_token()
// Returns the current token, without advancing to the next token in the input stream.
{
	token* result = new token();
	result = current_token;
	return result;
}
