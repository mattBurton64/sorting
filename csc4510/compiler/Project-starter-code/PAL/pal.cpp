/*************************************************************************************************
 *
 * PAL machine
 * (Pseudo Assembly Language interpreter)
 *
 * Author:     Michael Oudshoorn
 *             Webb School of Engineering
 *             High Point University
 *             High Point
 *             NC   27265
 *             USA
 *
 * Written:            1 May 2020
 * Last modified:      1 May 2020
 *
 * Open Source - free to distribute and modify. May not be used for profit.
 *
 * Written using C++20.
 *         g++ -std=c++2a -o pal pal.ccp
 *
 *
 * Usage
 *        pal [filename]
 * where filename contains the instruction code to be executed. If no filename is provided, then the
 * default file named "CODE" is used. If that is also not present, then an error is generated.
 *
 *
 * The PAL Machine
 *
 * Object Code Format
 *
 * The object code to be produced by your compiler is the machine language of the “PAL-machine”.
 & Object code instructions are to be written to a text file, one instruction per line, each using
 * one of the following formats:
 *
 *     <function code><integer number><integer number><comment>
 *     <function code><integer number><real number><comment>
 *     <function code><integer number><string><comment>
 *
 * The function code is a three-character code occupying the first three character positions of the
 * line, designating which instruction is intended.  The other fields of the instruction must be
 * separated by at least one blank.  Integer and real numbers follow the syntax of corresponding
 * lexical elements in Ada.  Strings are delimited by single quote characters.  Single quote
 * characters within the string are not repeated.  The comment is optional and is any sequence of
 * characters.
 *
 * The PAL-machine is a high-level, language-oriented computer that uses a “tagged” architecture.
 * It includes the concept of a “variable” (implemented as a level difference and a displacement)
 * and each location in memory has a type (“tag”).  The possible types are “bool”, “real”, “int”,
 * “string” and “undef”.
 *
 * PAL-machine Instructions
 *
 * MST    L    0    mark the stack
 * CAL    M    A    procedure call
 * INC    0    I    increment top-of-stack pointer
 * JIF    0    A    jump if false to address A
 * JMP    0    A    jump to address A
 * LCI    0    I    load integer constant onto the stack
 * LCR    0    R    load real constant onto the stack
 * LCS    0    S    load string literal onto the stack
 * LDA    L    D    load the absolute address of the variable onto the stack
 * LDI    0    0    load the value stored at the address indicated by the value at the top of stack
 * LDV    L    D    load the value of a variable onto the stack
 * LDU    0    0    load an undefined or void value
 * OPR    0    I    execute operation I
 * RDI    L    D    read a value into an integer variable
 * RDR    L    D    read a value into a real variable
 * STI    0    0    load top of stack -1 into variable at address top of stack
 * STO    L    D    store into a variable
 * SIG    0    I    raise signal I
 * REH    0    A    register exception handler at address A
 *
 * where    “A”    is an address in the instruction store
 *            “D”    is a displacement in the memory store
 *            “I”    is an integer number
 *            “L”    is a level difference
 *            “M”    is the number of parameters
 *            “R”    is a real number
 *            “S”    is a string
 *
 * The operations which may be executed by the OPR instruction are as follows:
 *
 *     0    procedure return
 *     1    function return
 *     2    negate
 *     3    addition
 *     4    subtraction
 *     5    multiplication
 *     6    division
 *     7    exponentiation
 *     8    string concatenation
 *     9    odd
 *     10    = (test for equality)
 *     11    /= (test for inequality)
 *     12    <
 *     13    >=
 *     14    >
 *     15    <=
 *     16    logical complement (not)
 *     17    true
 *     18    false
 *     19    eof
 *     20    write the integer, real or string value on top of the stack to the output file
 *     21    terminate the current line of the output file
 *     22    swap the top two elements of the stack
 *     23    duplicate the element on top of the stack
 *     24    drop the element on top of the stack
 *     25    integer-to-real conversion
 *     26    real-to-integer conversion
 *     27    integer-to-string conversion
 *     28    real-to-string conversion
 *     29    logical and
 *     30    logical or
 *     31    is(exception) – raises the exception matching the integer at the top of the stack
 *
 * The explanations for each of the instructions are as follows:
 *
 *
 * MST    L    0
 * Mark the stack frame.
 * Used in calling a procedure, the stack is firstly marked, then parameters are
 * loaded onto it and finally the call is executed.
 * L is the level difference between the call to the procedure and the declaration of the procedure.
 * For example, in the following
 *
 *         procedure A; begin ... end;
 *         procedure B; begin ... A ... end;
 *
 * the level difference is 1 between the call to A and the declaration of A, however with
 *
 *         procedure A;
 *             procedure B; begin ... end;
 *         begin ... B ... end;
 *
 * the level difference is 0 as procedure B is declared at the same level that it is called from.
 *
 *
 *  CAL    M    A
 * The new base is calculated from the current top-of-stack minus the parameters already
 * on the stack, where M is the number of parameters.  The return address is stored in the
 * frame base and the program counter jumps to the instruction at address A.
 *
 *
 *  INC    0    I
 * Increment the top-of-stack pointer.
 * The top-of-stack pointer is incremented by the integer I.  Any stack positions skipped through
 * the increment are given the type undefined.
 * This is generally used to allocate for variables.
 *
 *
 * JIF    0    A
 * Jump if false to address A.
 * If the element on top of stack is a bool
 * Then
 *         If the value on top of stack is false
 *         Then program register is assigned to be A
 *         If the program register is not inside the range of instructions
 *         Then an appropriate error message is issued and the program is halted.
 * Else an appropriate error message is issued.
 *
 *
 * JMP    0    A
 * Jump to address A.
 * The program register is assigned to be the integer value A.
 * If program register is outside the instruction range
 * Then an appropriate error message is issued and the program is halted.
 * "JMP 0 0" is the only way for a program to terminate normally.
 *
 *
 * LCI    0    I
 * Load integer constant onto stack.
 * Top-of-stack register is incremented by 1.
 * The new element at the top-of-stack is assigned to be of type integer and is given the integer
 * value I.
 *
 *
 * LCR    0    R
 * Load real constant onto stack.
 * Top-of-stack register is incremented by 1.
 * The new element at the top-of-stack is assigned to be of type real and is given the real value R.
 *
 *
 * LCS    0    S
 * Load string literal onto the stack.
 * Top-of-stack register is incremented by 1.
 * The new element at the top-of-stack is assigned to be of type string and is given the string
 * value S.
 *
 *
 * LDA    L    D
 * Load the address of a variable onto the top of the stack.
 * Top-of-stack register is incremented by 1.
 * The absolute address of the variable at stack location level difference L and displacement D is
 * loaded into the new top-of-stack position.
 *
 *
 * LDI    0    0
 * Load the value stored at the address indicated by the value at the top of stack
 * The value of the variable, whose address is specified in the top-of-stack position, is loaded
 * into the new top-of-stack position.  The top-of-stack register remains unchanged.
 *
 *
 * LDV    L    D
 * Load the value of a variable onto the top of the stack.
 * Top-of-stack register is incremented by 1.
 * The variable at stack location level difference L and displacement D is loaded into the new
 * top-of-stack position.
 *
 *
 * LDU    0    0
 * Load an undefined or void value onto the top of the stack.
 * Top-of-stack register is incremented by 1.
 *
 *
 * OPR    0    I
 *     0    {procedure return}
 *         Top of stack is returned to the current base - 1.  The program counter is set to the
 *         return address which is stored in the procedure stack frame and the base is set to the
 *        value of base before the procedure call.
 *     1    {function return}
 *         The value on the top of stack is assumed to be the function result.
 *        Top of stack is returned to the current base.  The program counter is set to the
 *         return address which is stored in the procedure stack frame and the base is set to the value
 *        of base before the procedure call.  The function result is placed in the new top of stack.
 *     2    {negate}
 *         If the value on top-of-stack is an integer or real
 *         Then the value on the top-of-stack is replaced by that value negated.
 *     3    {addition}
 *         If the elements which occupy the top and next to top positions on the stack are not both of
 *        type integer or real
 *        Then an error message is issued and the program is halted
 *         Else the value on top-of-stack is added to the value on top-of-stack - 1.
 *             Both of these values are removed from the stack and the result is
 *             placed on the new top-of-stack.
 *     4    {subtraction}
 *         If the elements which occupy the top and next to top positions on the stack are not both of
 *        type integer or real
 *        Then an error message is issued and the program is halted
 *         Else the value on top-of-stack is subtracted from the value on top-of-stack - 1.
 *             Both of these values are removed from the stack and the result is placed
 *             on the new top-of-stack.
 *     5    {multiplication}
 *         If the elements which occupy the top and next to top positions on the stack are not both of
 *         type integer or real
 *         Then an error message is issued and the program is halted
 *         Else the value on top-of-stack is multiplied by the value on top-of-stack - 1.
 *             Both of these values are removed from the stack and the result is placed
 *             on the new top-of-stack.
 *     6    {division}
 *         If the elements which occupy the top and next to top positions on the stack are not both
 *        of type integer or real
 *         Then an error message is issued and the program is halted
 *         Else
 *             If the value on top-of-stack is not 0.0
 *             Then the value on top-of-stack - 1 is divided by the value on top-of-stack.
 *                 Both of these values are removed from the stack and the result is
 *                 placed on the new top-of-stack.
 *     7    {exponentiation}
 *         Applies to the two elements occupying the top two positions of the stack.
 *         The value on top-of-stack must be an integer and that at the next-to-top position may be
 *        an integer or real; the type of the latter determines the type of the result.
 *         If the types of the top two elements on the stack are not consistent with this
 *        Then an error message is issued and the program is halted
 *         Else the value at the next-to-top position is raised to the power given by the value on
 *            top-of-stack.
 *            Both of these values are removed from the stack and the result is placed
 *            on the new top-of-stack.
 *    8    {string concatenation}
 *         If the value on top-of-stack is a string, and the value at top-of-stack – 1 is a string
 *         Then the string at the top-of-stack position is appended to the end of the string and the
 *            top-of-stack – 1 position.
 *            Both of these values are removed from the stack and the result is placed on the
 *            new top-of-stack,
 *         Else an error message is issued and the program is halted.
 *     9    {odd}
 *         If the value on the top-of-stack is an integer
 *         Then
 *             If the value on top-of-stack is odd
 *             Then replace the top-of-stack element with the boolean value true
 *             Else replace the top-of-stack with the boolean value false
 *         Else an error message is issued and the program is halted.
 *     10    {=}
 *         Applies to the elements that occupy the next-to-top and top positions on the stack.
 *         If these elements are both of type integer or real
 *         Then the element on the top of the stack is removed from the stack and the next-to-top
 *            element is replaced by the boolean element true or false.
 *     11    {/=}
 *         Applies to the elements that occupy the next-to-top and top positions on the stack.
 *         If these elements are both of type integer or real
 *         Then the top-of-stack element is removed from the stack and the next-to-top element
 *            is replaced by the boolean element true or false.
 *     12    {<}
 *         Applies to the elements that occupy the next-to-top and top positions on the stack.
 *         If these elements are both of type integer or real
 *         Then the top-of-stack element is removed from the stack and the next-to-top element
 *            is replaced by the boolean element true or false.
 *     13    {>=}
 *         Applies to the elements that occupy the next-to-top and top positions on the stack.
 *         If these elements are both of type integer or real
 *         Then  the top-of-stack element is removed from the stack and the next-to-top element
 *            is replaced by the boolean element true or false.
 *     14    {>}
 *         Applies to the elements that occupy the next-to-top and top positions on the stack.
 *         If these elements are both of type integer or real
 *         Then  the top-of-stack element is removed from the stack and the next-to-top element
 *            is replaced by the boolean element true or false.
 *     15    {<=}
 *         Applies to the elements that occupy the next-to-top and top positions on the stack.
 *         If these elements are both of type integer or real
 *         Then  the top-of-stack element is removed from the stack and the next-to-top element
 *            is replaced by the boolean element true or false.
 *     16    {logical complement (not)}
 *         If the element which occupies the top position on the stack is a bool
 *         Then the element is replaced on the top of the stack by its logical complement
 *         Else an appropriate error message is issued and the program is halted.
 *     17    {true}
 *         Put the boolean element true on top of the stack.
 *     18    {false}
 *         Put the boolean operator false on the top of the stack.
 *     19    {eof}
 *         If end of file has been reached
 *         Then put the boolean value true on the top of the stack
 *         Else put the boolean value false on the top of the stack.
 *     20    {write the integer, real, or string value on top of the stack to the output file}
 *         If the element on top of stack is of type integer, bool, real or string
 *         Then it is removed from the top of the stack and written to output
 *         Else (it is of type bool or undefined) an appropriate error message is issued and
 *            the program is halted.
 *     21    {terminate the current line of the output file}
 *         A newline command is written to output.
 *     22    {swap the top two elements of the stack}
 *         The elements on top of the stack and top of stack -1 are swapped.
 *     23    {duplicate the element on top of the stack}
 *         The element on top of the stack is duplicated and the new element is placed on top
 *            of the stack.
 *     24    {drop the element on top of the stack}
 *         The element on top of the stack is dropped from the stack.
 *     25    {integer-to-real conversion}
 *         If the value on top-of-stack is an integer
 *         Then this value is replaced on the stack by the integer to real conversion of this value
 *         Else an error message is issued and the program is halted.
 *     26    {real-to-integer conversion}
 *         If the value on top-of-stack is a real
 *         Then this value is replaced on the stack by the real to integer conversion of this value
 *         Else an error message is issued and the program is halted.
 *     27    {integer-to-string conversion}
 *         If the value on top-of-stack is an integer
 *         Then this value is replaced on the stack by the integer to string conversion of this value
 *         Else an error message is issued and the program is halted.
 *     28    {real-to-string conversion}
 *         If the value on top-of-stack is an real
 *         Then this value is replaced on the stack by the real to string conversion of this value
 *         Else an error message is issued and the program is halted.
 *     29    {logical and}
 *         If the elements which occupy the top two positions on the stack are bool
 *         Then the elements are replaced by the logical and of the boolean values
 *         Else an appropriate error message is issued and the program is halted.
 *     30    {logical or}
 *         If the elements which occupy the top two positions on the stack are bool
 *         Then the elements are replaced by the logical or of the boolean values
 *         Else an appropriate error message is issued and the program is halted.
 *     31    {is(exception)}
 *         The element on the top of the stack is an integer that represents an exception type.
 *         This function pops the value and pushes a boolean value indicating if the current
 *        exception type matches.
 *
 *
 * RDI    L    D
 * Read a value into an integer variable.
 * At the stack location level difference L and displacement D,
 * assign the type of the element to be int, and
 * assign the value to be that of the integer value read in from the next line of the input file.
 * If eof was read
 * Then an appropriate error message is issued and the program is halted.
 *
 *
 * RDR    L    D
 * Read a value into a real variable.
 * At the stack location level difference L and displacement D,
 * assign the type of the element to be real, and
 * assign the value to be that of the real or integer value read in from the next line of
 * the input file.
 * If eof was read
 * Then an appropriate error message is issued and the program is halted.
 *
 *
 * STI    0    0
 * Load the element in top-of-stack - 1 into the variable at the address specified by
 * the element on the top-of-stack.
 * The top two elements are removed from the stack.
 *
 *
 * STO    L    D
 * Store into a variable.
 * Load the element on the top-of-stack into the stack location level difference L and
 * displacement D and remove that element from the top of the stack.
 * If they are not of precisely the same type an error message is issued and the program is halted.
 *
 *
 * SIG    0    I
 * Raise a signal/exception.
 * This instruction causes the entire run–time stack to be searched looking for an exception
 * handler which deals with the particular exception indicated.  If a handler is found, all
 * activation records down to the frame that contains the handler are discarded.  Control is
 * transferred to the exception handler.
 * The following exceptions are deﬁned:
 *         0    Re-raise the present active signal
 *             This will the current signal to be re–raised and the current block to terminate.
 *         1    Program Abort
 *             This signal will cause termination of the program.  Can not be intercepted.
 *         2    No return in function
 *             No “return” value was generated for this function.
 *         3    Type mis-match in input
 *             RDI or RDR found a value which was neither integer nor real.
 *         4    Attempt to read past end of ﬁle
 *             End of ﬁle was true before RDI or RDR were executed.
 *
 *
 * REH    0    A
 * Register exception handler at address A
 * Address “A” is stored in the stack mark as the exception handling code for this stack frame.
 * A list of built–in exceptions is given in the description of the “SIG” instruction.  An address
 * of zero indicates that no exception handler is registered.
 *
 *
 * The PAL stack mark uses 4 locations:
 *        +----------------------------+
 *      | Exception handler address  |
 *        +----------------------------+
 *      | Return point address       |
 *        +----------------------------+
 *      | Dynamic link                  |
 *        +----------------------------+
 *      | Static link                |
 *        +----------------------------+
 *
 *
 *************************************************************************************************/

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <chrono>
#include <map>
#include <vector>
#include <iterator>

#include "Memory_cell.h"

using namespace std;
using namespace std::chrono;

// Global variables follow.

// flags
bool debugging_pal_code { false };

// constexpr int data_alloc_index { 3 };     // Space for return links etc on the stack
// constexpr int lev_max { 5 };             // Maximum depth of block nesting
constexpr int code_size { 10000 };            // Size of instruction store
constexpr int store_size { 10000 };         // Size of data store

enum fun_code    // Function codes in the PAL instruction set
{
    fun_MST,    // Mark the stack
    fun_CAL,    // Procedure call
    fun_INC,    // Increoment top-of-stack pointer
    fun_JIF,    // Jump if false
    fun_JMP,    // Inconditinoal jump
    fun_LCI,    // Load integer constant onto stack
    fun_LCR,    // Load real constant onto stack
    fun_LCS,    // Load string literal onto stack
    fun_LDA,    // Load the absolute address of a variable onto the stack
    fun_LDI,    // Load the value stored at specifed address onto the stack
    fun_LDV,    // Load the value of a variable onto the stack
    fun_LDU,    // Load an undefined or void value
    fun_OPR,    // Execute operation - there are 32 of them
    fun_RDI,    // Read a value into an integer variable
    fun_RDR,    // Read a value into a real variable
    fun_STI,    // Load top-of-stack - 1 into a variable at address top-of-stack
    fun_STO,    // Store into a variable
    fun_SIG,    // Raise signal
    fun_REH,    // Register exception handler
    fun_DBG     // Turn debugging status on/off
};

// set up mapping from string to function codes;
map<string, fun_code> fun_code_map;

Memory_cell data_store[store_size] { Memory_cell() }; // Define data memory (RAM)

constexpr int instruction_size { 3 };     // Each instruction consists of 3 components.

struct instruction                        // Description of a single instruction
{
    fun_code f { fun_MST };                // Function code
    int l { 0 };                        // Level difference
    Memory_cell a;    // Offset address or constant value
};


instruction code_store[code_size];        // Instruction store
// Note that the data store and instruction store are separated for convenience.

// The PAL machine has a number of predefined exceptions
constexpr int re_raise_exception { 0 };
constexpr int program_abort_exception { 1 };
constexpr int no_return_in_function_exception { 2 };    // Used in compiler
constexpr int input_error_exception { 3 };
constexpr int end_error_exception { 4 };
constexpr int abort_program_exception { 5 };
constexpr int other_exception { 6 };

int pal_exception { program_abort_exception };  // Name of the current exception

int last_instruction { 0 };      // Index of last instruction loaded into code_store

ifstream code_file;                // Read-only file containing the PAL instructions
// generated by the compiler.

string default_code_file_name { "CODE" };    // Name of default code file.

// registers
int program_counter { 0 };
int base_register { 0 };
int top_of_stack { 0 };
instruction *instruction_register;

void establish_function_mapping()
{
    // Set up mapping of strings onto function codes.
    // insert elements into the map
    fun_code_map.insert(pair<string, fun_code>("MST", fun_MST)); // Mark the stack
    fun_code_map.insert(pair<string, fun_code>("CAL", fun_CAL)); // Procedure call
    fun_code_map.insert(pair<string, fun_code>("INC", fun_INC)); // Increment top-of-stack pointer
    fun_code_map.insert(pair<string, fun_code>("JIF", fun_JIF)); // Jump if false
    fun_code_map.insert(pair<string, fun_code>("JMP", fun_JMP)); // Unconditional jump
    fun_code_map.insert(pair<string, fun_code>("LCI", fun_LCI)); // Load integer constant onto stack
    fun_code_map.insert(pair<string, fun_code>("LCR", fun_LCR)); // Load real constant onto stack
    fun_code_map.insert(pair<string, fun_code>("LCS", fun_LCS)); // Load string literal onto stack
    fun_code_map.insert(pair<string, fun_code>("LDA", fun_LDA)); // Load the absolute address of a variable onto the stack
    fun_code_map.insert(pair<string, fun_code>("LDI", fun_LDI)); // Load the value stored at specified address onto the stack
    fun_code_map.insert(pair<string, fun_code>("LDV", fun_LDV)), // Load the value of a variable onto the stack
    fun_code_map.insert(pair<string, fun_code>("LDU", fun_LDU)); // Load an undefined or void value
    fun_code_map.insert(pair<string, fun_code>("OPR", fun_OPR)); // Execute operation - there are 32 of them
    fun_code_map.insert(pair<string, fun_code>("RDI", fun_RDI)); // Read a value into an integer variable
    fun_code_map.insert(pair<string, fun_code>("RDR", fun_RDR)); // Read a value into a real variable
    fun_code_map.insert(pair<string, fun_code>("STI", fun_STI)); // Load top-of-stack - 1 into a variable at address top-of-stack
    fun_code_map.insert(pair<string, fun_code>("STO", fun_STO)); // Store into a variable
    fun_code_map.insert(pair<string, fun_code>("SIG", fun_SIG)); // Raise signal
    fun_code_map.insert(pair<string, fun_code>("REH", fun_REH)); // Register exception handler
    fun_code_map.insert(pair<string, fun_code>("DBG", fun_DBG)); // Turn debugging status on/off
}


fun_code strtofun(string s)
// return the function code associated with string
{
    return fun_code_map.find(s)->second;
}

string funtostr(fun_code f)
{
    string key = "";
    for (auto &i : fun_code_map) {
        if (i.second == f) {
            key = i.first;
            break; // to stop searching
        }
    }
    return key;
}


string insttostr(instruction i)
// Convert an instruction to a string
{
    return funtostr(i.f) + " " + to_string(i.l) + " " + i.a.to_string();
}

void trace_stack(int p, int b, int t)
// Trace the stack and create a stack dump
{
    cout << endl << "*** Run-time stack:" << endl;
    cout << "     Base of activation record: " << b << "." << endl;
    cout << "     Current top of stack: " << t << "." << endl;
    cout << "     Instruction register contains: '"
            << insttostr(*instruction_register) << "'." << endl;
    cout << endl;
    cout << "Contents of stack:" << endl;
    cout << "------------------" << endl << endl;
    for (int i = 1; i <= t; i++) {
        cout << "   " << i << ": '" << data_store[i].to_string() << "'."
                << endl;
    }
    cout << endl << endl;
}


void unwind(int exc, int lp, int lb, int &lt);    // forward declaration


void error(string message, int exc = program_abort_exception)
// Non-fatal error detected. Provide stack dump.
{
    cerr << "*** Run-time error: " << message << endl;
    cerr << "     At address: " << (program_counter - 1) << "." << endl;
    trace_stack(base_register, program_counter, top_of_stack);
    cerr << endl << endl;
    unwind(exc, program_counter, base_register, top_of_stack);
    ;
}


void fatal_error(string message)
// Fatal run-time error detected
        {
    cerr << "*** FATAL Run-time error: " << message << endl;
    cerr << "     At address: " << (program_counter - 1) << "." << endl;
    trace_stack(base_register, program_counter, top_of_stack);
    cerr << endl;
    abort();
}


int base(int l)
// Find base l levels down
        {
    int lev { l };
    int b1 = { base_register };
    while (lev > 0) {
        if (data_store[b1 - 4].is_int())
            b1 = data_store[b1 - 4].get_int();
        else
            error("Static link is not an integer.");
        lev--;
    }
    return b1;
}


void unwind(int exc, int lp, int lb, int &lt)
// Exception exc has occurred. Look for an exception handler and discard stack frames
// until one is found.
// lp, lb, lt are the corresponding program counter, base and top of the target handler (if found).
        {
    bool exit_loop { false };

    while (!exit_loop) {
        if (debugging_pal_code) {
            cout << "Unwinding" << endl;
            trace_stack(lp, lb, lt);
            cout << endl;
        }
        if (data_store[lb - 1].is_int()) {
            // Might be a handler
            if (data_store[lb - 1].get_int() != 0) {
                // Looking hopeful.
                if ((data_store[lb - 1].get_int() > 0)
                        and (data_store[lb - 1].get_int() < last_instruction)) {
                    // A valid handler has been found!
                    if (debugging_pal_code)
                        cout << "Exception handler found." << endl;
                    lp = data_store[lb - 1].get_int();
                    exit_loop = true;
                } else {
                    // Exception handler address is invalid.
                    fatal_error("Exception handler address is invalid");
                }
            } else {
                // No handler in this frame +> discard it.
                if (debugging_pal_code)
                    cout << "No handler in this frame." << endl;
                lt = lb - 5;
                lp = data_store[lt + 3].get_int();
                lb = data_store[lt + 2].get_int();
                if (lb == 0)
                    fatal_error("Exception never handled.");
            }
        } else
            fatal_error("Exception handler address has the wrong type!");
    }
    top_of_stack = lt;
    if (debugging_pal_code) {
        cout << "Unwinding" << endl;
        trace_stack(lp, lb, lt);
    }
}


void execute_code() {
    // initialize registers
    top_of_stack = 4;
    base_register = 5;
    program_counter = 1;
    Memory_cell temp;
    
    // set up the main program activation record
    for (int i = 1; i <= 4; i++) {
        data_store[i] = Memory_cell(0);
    }

    do    // ready to start executing the PAL code
    {
        if (debugging_pal_code) {
            // Some useful debugging code...
            cout << endl << "Instruction at " << program_counter << ": "
                    << funtostr(code_store[program_counter].f) << " "
                    << code_store[program_counter].l << " ";
            switch (code_store[program_counter].a.get_type()) {
            case Memory_cell::types_UNDEF:
                cout << "UNDEFINED" << endl;
                break;
            case Memory_cell::types_BOOLEAN:
                cout << code_store[program_counter].a.get_boolean() << endl;
                break;
            case Memory_cell::types_INT:
                cout << code_store[program_counter].a.get_int() << endl;
                break;
            case Memory_cell::types_REAL:
                cout << code_store[program_counter].a.get_real() << endl;
                break;
            case Memory_cell::types_STRING:
                cout << code_store[program_counter].a.get_string() << endl;
                break;
            default:   // should never arise since all cases are addressed above
                break;
            }
            // end of useful debugging code
        }

        instruction_register = &code_store[program_counter]; // note the instruction we are about to execute
        program_counter++;

        // large switch statement (ugly) to go through each instruction....
        switch (instruction_register->f) {
        case fun_MST:    // Mark the stack
            data_store[top_of_stack + 1].set_int(base(instruction_register->l));
            data_store[top_of_stack + 2].set_int(base_register);
            data_store[top_of_stack + 3].set_int(0);
            data_store[top_of_stack + 4].set_int(0);
            top_of_stack = top_of_stack + 4;

            break;
        case fun_CAL:    // Procedure or function call
            base_register = top_of_stack - instruction_register->l + 1;
            data_store[base_register - 2].set_int(program_counter);
            program_counter = instruction_register->a.get_int();
            break;
        case fun_INC:    // Increment top-of-stack pointer
            if (instruction_register->a.get_int() > 0)
                for (int i = top_of_stack + 1;
                        i <= top_of_stack + instruction_register->a.get_int();
                        i++)
                    data_store[i].set_undef();
            top_of_stack += instruction_register->a.get_int();
            break;
        case fun_JIF:    // Jump if false
            if (data_store[top_of_stack].is_boolean()) {
                if (!data_store[top_of_stack].get_boolean()) {
                    program_counter = instruction_register->a.get_int();
                    if ((program_counter < 0)
                            || (program_counter > last_instruction))
                        error("Attempt to jump outside code.");
                }
                // else nothing to do
            } else
                error("JIF - top of stack not a boolean.");
            break;
        case fun_JMP:    // Inconditinoal jump
            program_counter = instruction_register->a.get_int();
            if ((program_counter < 0) || (program_counter > last_instruction))
                error("Attempt to jump outside code.");
            break;
        case fun_LCI:    // Load integer constant onto stack
            top_of_stack++;
            data_store[top_of_stack].set_int(instruction_register->a.get_int());
            break;
        case fun_LCR:    // Load real constant onto stack
            top_of_stack++;
            data_store[top_of_stack].set_real(
                    instruction_register->a.get_real());
            break;
        case fun_LCS:    // Load string literal onto stack
            top_of_stack++;
            data_store[top_of_stack].set_string(
                    instruction_register->a.get_string());
            break;
        case fun_LDA:  // Load the absolute address of a variable onto the stack
            top_of_stack++;
            data_store[top_of_stack].set_int(
                    base(instruction_register->l)
                            + instruction_register->a.get_int());
            break;
        case fun_LDI: // Load the value stored at specifed address onto the stack
            data_store[top_of_stack] =
                    data_store[data_store[top_of_stack].get_int()];
            break;
        case fun_LDV:    // Load the value of a variable onto the stack
            top_of_stack++;
            data_store[top_of_stack] = data_store[base(instruction_register->l)
                    + instruction_register->a.get_int()];
            break;
        case fun_LDU:    // Load an undefined or void value
            top_of_stack++;
            data_store[top_of_stack].set_undef();
            break;
        case fun_RDI:    // Read a value into an integer variable
        {
            int temp;
            cin >> temp;
            data_store[base(instruction_register->l)
                    + instruction_register->a.get_int()].set_int(temp);
        }
            break;
        case fun_RDR:    // Read a value into a real variable
        {
            float temp;
            cin >> temp;
            data_store[base(instruction_register->l)
                    + instruction_register->a.get_int()].set_real(temp);
        }
            break;
        case fun_STI: // Load top-of-stack - 1 into a variable at address top-of-stack
            data_store[data_store[top_of_stack].get_int()] =
                    data_store[top_of_stack - 1];
            top_of_stack -= 2;
            break;
        case fun_STO:    // Store into a variable
            data_store[base(instruction_register->l)
                    + instruction_register->a.get_int()] =
                    data_store[top_of_stack];
            top_of_stack--;
            break;
        case fun_SIG:    // Raise signal
            if (instruction_register->a.get_int() != 0)
                pal_exception = instruction_register->a.get_int();
            break;
        case fun_REH:    // Register exeception handler
            data_store[base_register - 1].set_int(
                    instruction_register->a.get_int());
            break;
        case fun_DBG:    // Turn debugging status on/off
            debugging_pal_code = (instruction_register->a.get_int() == 1);
            break;
        case fun_OPR:    // Execute operation - there are 32 of them
            // There are 32 operations that need to be handled
            switch (instruction_register->a.get_int()) {
            case 0:    // procedure return
                if (debugging_pal_code)
                    trace_stack(program_counter, base_register, top_of_stack);
                top_of_stack = base_register - 5;
                program_counter = data_store[top_of_stack + 3].get_int();
                base_register = data_store[top_of_stack + 2].get_int();
                break;
            case 1:     // function return
                if (debugging_pal_code)
                    trace_stack(program_counter, base_register, top_of_stack);
                temp = data_store[top_of_stack];
                top_of_stack = base_register - 5;
                program_counter = data_store[top_of_stack + 3].get_int();
                base_register = data_store[top_of_stack + 2].get_int();
                data_store[++top_of_stack] = temp;
                break;
            case 2:    // negate
                if (data_store[top_of_stack].is_real()) {
                    data_store[top_of_stack].set_real(
                            -data_store[top_of_stack].get_real());
                } else if (data_store[top_of_stack].is_int()) {
                    data_store[top_of_stack].set_int(
                            -data_store[top_of_stack].get_int());
                } else {
                    error("Cannot negate boolean or string value.");
                }
                break;
            case 3:    // addition
            case 4:    // subtraction
            case 5:    // multiplication
            case 6:    // division
                // deal with all the mathematical operators at once.
                top_of_stack--;
                if (data_store[top_of_stack].get_type()
                        != data_store[top_of_stack + 1].get_type()) {
                    error("Operands must be of the same type.");
                } else {
                    switch (data_store[top_of_stack].get_type()) {
                    case Memory_cell::types_INT:
                        switch (instruction_register->a.get_int()) {
                        case 3:        // addition
                            data_store[top_of_stack].set_int(
                                    data_store[top_of_stack].get_int()
                                            + data_store[top_of_stack + 1].get_int());
                            break;
                        case 4:        // subtraction
                            data_store[top_of_stack].set_int(
                                    data_store[top_of_stack].get_int()
                                            - data_store[top_of_stack + 1].get_int());
                            break;
                        case 5:        // multiplication
                            data_store[top_of_stack].set_int(
                                    data_store[top_of_stack].get_int()
                                            * data_store[top_of_stack + 1].get_int());
                            break;
                        case 6:        // division
                            if (data_store[top_of_stack + 1].get_int() != 0) {
                                data_store[top_of_stack].set_int(
                                        data_store[top_of_stack].get_int()
                                                / data_store[top_of_stack + 1].get_int());
                            } else {
                                error("Divide by integer 0.");
                            }
                            break;
                        default:    // should never be selected
                            break;
                        } // end switch
                        break;
                    case Memory_cell::types_REAL:
                        switch (instruction_register->a.get_int()) {
                        case 3:        // addition
                            data_store[top_of_stack].set_real(
                                    data_store[top_of_stack].get_real()
                                            + data_store[top_of_stack + 1].get_real());
                            break;
                        case 4:        // subtraction
                            data_store[top_of_stack].set_real(
                                    data_store[top_of_stack].get_real()
                                            - data_store[top_of_stack + 1].get_real());
                            break;
                        case 5:        // multiplication
                            data_store[top_of_stack].set_real(
                                    data_store[top_of_stack].get_real()
                                            * data_store[top_of_stack + 1].get_real());
                            break;
                        case 6:        // division
                            if (data_store[top_of_stack + 1].get_real()
                                    != 0.0) {
                                data_store[top_of_stack].set_real(
                                        data_store[top_of_stack].get_real()
                                                / data_store[top_of_stack + 1].get_real());
                            } else {
                                error("Divide by floating point 0.0.");
                            }
                            break;
                        default:    // should never be selected
                            break;
                        } // end switch
                        break;
                    default:
                        error("Operands must be integer or real");
                        break;
                    } // end switch
                } // end if
                break;
            case 7:    // exponentiation
                top_of_stack--;
                if (data_store[top_of_stack + 1].get_type()
                        != Memory_cell::types_INT) {
                    error("Exponent must be an integer.");
                } else {
                    switch (data_store[top_of_stack].get_type()) {
                    case Memory_cell::types_INT: {
                        int temp;

                        temp = data_store[top_of_stack].get_int();
                        if (data_store[top_of_stack + 1].get_int() == 0) {
                            temp = 1;
                        } else {
                            for (int j = 1;
                                    j
                                            <= data_store[top_of_stack + 1].get_int()
                                                    - 1; j++) {
                                temp *= data_store[top_of_stack].get_int();
                            }
                        }
                        data_store[top_of_stack].set_int(temp);
                    }
                        break;
                    case Memory_cell::types_REAL: {
                        float temp;

                        temp = data_store[top_of_stack].get_real();
                        if (data_store[top_of_stack + 1].get_int() == 0) {
                            temp = 1;
                        } else {
                            for (int j = 1;
                                    j
                                            <= data_store[top_of_stack + 1].get_int()
                                                    - 1; j++) {
                                temp *= data_store[top_of_stack].get_real();
                            }
                        }
                        data_store[top_of_stack].set_real(temp);
                    }
                        break;
                    default:
                        error("Operand must be an integer or a floating point");
                        break;
                    } // end switch
                } // end if
                break;
            case 8:    // string concatenation
                if (data_store[top_of_stack].get_type()
                        != Memory_cell::types_STRING) {
                    error(
                            "String concatenation requires String on top of stack.");
                } else if (data_store[top_of_stack - 1].get_type()
                        != Memory_cell::types_STRING) {
                    error(
                            "String concatenation requires String on top of stack - 1.");
                } else {
                    data_store[top_of_stack - 1].set_string(
                            data_store[top_of_stack - 1].get_string()
                                    + data_store[top_of_stack].get_string());
                }
                top_of_stack--;
                break;
            case 9:    // odd
                if (data_store[top_of_stack].get_type()
                        != Memory_cell::types_INT) {
                    error("Odd instruction expects integer value.");
                } else {
                    data_store[top_of_stack].set_boolean(
                            data_store[top_of_stack].get_int() % 2 == 1);
                }
                break;
            case 10:    // =
            case 11:    // !=
            case 12:    // <
            case 13:    // >=
            case 14:    // >
            case 15:    // <=        Handle comparators together
                top_of_stack--;
                if (data_store[top_of_stack].get_type()
                        != data_store[top_of_stack + 1].get_type()) {
                    error("operands must be of the same type.");
                } else {
                    switch (data_store[top_of_stack].get_type()) {
                    case Memory_cell::types_BOOLEAN:
                        switch (instruction_register->a.get_int()) {
                        case 10:      // =
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_boolean()
                                            == data_store[top_of_stack + 1].get_boolean());
                            break;
                        case 11:    // !=
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_boolean()
                                            != data_store[top_of_stack + 1].get_boolean());
                            break;
                        case 12:    // <
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_boolean()
                                            < data_store[top_of_stack + 1].get_boolean());
                            break;
                        case 13:    // >=
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_boolean()
                                            >= data_store[top_of_stack + 1].get_boolean());
                            break;
                        case 14:    // >
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_boolean()
                                            > data_store[top_of_stack + 1].get_boolean());
                            break;
                        case 15:    // <=
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_boolean()
                                            <= data_store[top_of_stack + 1].get_boolean());
                            break;
                        default:    // Should never be invoked
                            break;
                        }
                        break;
                    case Memory_cell::types_INT:
                        switch (instruction_register->a.get_int()) {
                        case 10:      // =
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_int()
                                            == data_store[top_of_stack + 1].get_int());
                            break;
                        case 11:    // !=
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_int()
                                            != data_store[top_of_stack + 1].get_int());
                            break;
                        case 12:    // <
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_int()
                                            < data_store[top_of_stack + 1].get_int());
                            break;
                        case 13:    // >=
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_int()
                                            >= data_store[top_of_stack + 1].get_int());
                            break;
                        case 14:    // >
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_int()
                                            > data_store[top_of_stack + 1].get_int());
                            break;
                        case 15:    // <=
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_int()
                                            <= data_store[top_of_stack + 1].get_int());
                            break;
                        default:    // Should never be invoked
                            break;
                        }
                        break;
                    case Memory_cell::types_REAL:
                        switch (instruction_register->a.get_int()) {
                        case 10:      // =
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_real()
                                            == data_store[top_of_stack + 1].get_real());
                            break;
                        case 11:    // !=
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_real()
                                            != data_store[top_of_stack + 1].get_real());
                            break;
                        case 12:    // <
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_real()
                                            < data_store[top_of_stack + 1].get_real());
                            break;
                        case 13:    // >=
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_real()
                                            >= data_store[top_of_stack + 1].get_real());
                            break;
                        case 14:    // >
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_real()
                                            > data_store[top_of_stack + 1].get_real());
                            break;
                        case 15:    // <=
                            data_store[top_of_stack].set_boolean(
                                    data_store[top_of_stack].get_real()
                                            <= data_store[top_of_stack + 1].get_real());
                            break;
                        default:    // Should never be invoked
                            break;
                        }
                        break;
                    default:
                        error(
                                "Operands must in integer, floating point, or boolean.");
                        break;
                    }
                }
                break;
            case 16:     // logical complement (not)
                if (data_store[top_of_stack].get_type()
                        != Memory_cell::types_BOOLEAN) {
                    error(
                            "not operation expects boolean value on top of stack.");
                } else {
                    data_store[top_of_stack].set_boolean(
                            !data_store[top_of_stack].get_boolean());
                }
                break;
            case 17:    // true
                top_of_stack++;
                data_store[top_of_stack].set_boolean(true);
                break;
            case 18:    // false
                top_of_stack++;
                data_store[top_of_stack].set_boolean(false);
                break;
            case 19:    // eof
                top_of_stack++;
                data_store[top_of_stack].set_boolean(cin.eof());
                break;
            case 20: // write the integer ! float ! string of top of stack to output
                switch (data_store[top_of_stack].get_type()) {
                case Memory_cell::types_REAL:
                    cout << data_store[top_of_stack].get_real();
                    break;
                case Memory_cell::types_INT:
                    cout << data_store[top_of_stack].get_int();
                    break;
                case Memory_cell::types_STRING:
                    cout << data_store[top_of_stack].get_string();
                    break;
                default:
                    error("Can only write integer, floating point, and string values.");
                    break;
                }
                top_of_stack--;
                break;
            case 21:    // terminate the current line of output
                cout << endl;
                break;
            case 22:     // swap the top two elements on the stack
            {
                Memory_cell temp;
                temp = data_store[top_of_stack];
                data_store[top_of_stack] = data_store[top_of_stack - 1];
                data_store[top_of_stack - 1] = temp;
            }
                break;
            case 23:    // duplicate the element on the top of the stack
                top_of_stack++;
                data_store[top_of_stack] = data_store[top_of_stack - 1];
                break;
            case 24:    // drop the element on th etop of the stack
                top_of_stack--;
                break;
            case 25:    // integer-to-real conversion
                if (data_store[top_of_stack].get_type()
                        != Memory_cell::types_INT) {
                    error(
                            "int-to-real conversion expects integer on top of stack.");
                } else {
                    data_store[top_of_stack].set_real(
                            float(data_store[top_of_stack].get_int()));
                }
                break;
            case 26:    // real-to-integer conversion
                if (data_store[top_of_stack].get_type()
                        != Memory_cell::types_REAL) {
                    error(
                            "real-to_int conversion expects real number on top of stack.");
                } else {
                    data_store[top_of_stack].set_int(
                            int(data_store[top_of_stack].get_real()));
                }
                break;
            case 27:    // integer-to-string conversion
                if (data_store[top_of_stack].get_type()
                        != Memory_cell::types_INT) {
                    error(
                            "int-to-string conversion expects integer on top of stack.");
                } else {
                    data_store[top_of_stack].set_string(
                            to_string(data_store[top_of_stack].get_int()));
                }
                break;
            case 28:    // real-to-string conversion
                if (data_store[top_of_stack].get_type()
                        != Memory_cell::types_REAL) {
                    error(
                            "real-to-string conversion expects integer on top of stack.");
                } else {
                    data_store[top_of_stack].set_string(
                            to_string(data_store[top_of_stack].get_real()));
                }
                break;
            case 29:    // logical and
                if ((data_store[top_of_stack].get_type()
                        != Memory_cell::types_BOOLEAN)
                        && data_store[top_of_stack - 1].get_type()
                                != Memory_cell::types_BOOLEAN) {
                    error(
                            "Logical and expects boolean values at top of stack, and top of stack-1");
                } else {
                    data_store[top_of_stack - 1].set_boolean(
                            data_store[top_of_stack - 1].get_boolean()
                                    && data_store[top_of_stack].get_boolean());
                    top_of_stack--;
                }
                break;
            case 30:    // logical or
                if ((data_store[top_of_stack].get_type()
                        != Memory_cell::types_BOOLEAN)
                        && data_store[top_of_stack - 1].get_type()
                                != Memory_cell::types_BOOLEAN) {
                    error(
                            "Logical or expects boolean values at top of stack, and top of stack-1");
                } else {
                    data_store[top_of_stack - 1].set_boolean(
                            data_store[top_of_stack - 1].get_boolean()
                                    || data_store[top_of_stack].get_boolean());
                    top_of_stack--;
                }
                break;
            case 31:    // is(exception)
                if (data_store[top_of_stack].get_type()
                        != Memory_cell::types_INT) {
                    error(
                            "is operations expects an integer value on top of stack");
                } else {
                    data_store[top_of_stack].set_boolean(
                            data_store[top_of_stack].get_int()
                                    == pal_exception);
                }
                break;
            default: // should not be called since all cases have been enumerated
                break;
            }
            break;
        default:    // Should not occur. All possible cases are identified above
            break;
        }
        if (debugging_pal_code)
            trace_stack(program_counter, base_register, top_of_stack);
    } while (program_counter != 0);

}


vector<string> tokenize(const string &s) {
    // identify each token in the string separated by white space.
    auto end = s.cend();
    auto start = end;

    vector < string > v;
    for (auto it = s.cbegin(); it != end; ++it) {
        if (!isspace(*it)) {
            if (start == end)
                start = it;
            continue;
        }
        if (start != end) {
            v.emplace_back(start, it);
            start = end;
        }
    }
    if (start != end)
        v.emplace_back(start, end);
    return v;
}


void load(ifstream &code_file) {
    string line;    // read code_file in line by line.

    vector < string > tokens;    // break each line into a vector of tokens

    // map<string, fun_code>::iterator it;
    fun_code instr; // the instruction currently being uploaded into the code store.

    int top { 0 };
    int lev_diff { 0 };
    int pos { 0 };
    string str;

    // We know the file is open and non-empty when we reach this point.
    while (getline(code_file, line)) {
        top++; // Increment top point. This is the cell in the code store we are populating.

        // line must adhere to a strict structure otherwise raise an exception and abort
        try {
            if (debugging_pal_code)
                cout << top << ":    " << line << endl;
            tokens = tokenize(line); // white space separates each token in the line.

            // Every PAL instruction is on one line.
            // Every PAL instruction has 3 fields followed by comments
            // Comments are ignored, so only the first 3 tokens are useful.

            if (tokens.size() < instruction_size) {
                // There are 3 required components for every instruction.
                throw("Instruction malformed: " + line);
            } else {
                // The first token is the instruction
                // Convert first token to upper case so it can be used with map.
                for (auto &c : tokens.at(0)) {
                    c = toupper(c);
                }
                if (fun_code_map.find(tokens.at(0)) == fun_code_map.end()) {
                    // Invalid instruction
                    throw("Illegal instruction: " + tokens.at(0));
                }
                instr = strtofun(tokens.at(0));
                // Second field is the level difference. it must be an integer.
                lev_diff = stoi(tokens.at(1));

                if (top >= code_size) {
                    // Exceeded capacity of code store
                    throw "Too many instructions. Code store full.";
                }
                code_store[top].f = instr;            // Set function code field
                code_store[top].l = lev_diff;       // Set level difference field

                // Third field is dependent on the instruction.
                if (instr == fun_LCR) {
                    code_store[top].a = Memory_cell(stof(tokens.at(2)));
                } else if (instr == fun_LCS) {
                    // Handle strings...
                    str = "";    // initialize the string to empty

                    // We know line contains at least 3 tokens and that they are
                    // separated by whitespace.
                    // Find the beginning of the third token.
                    pos = 0; // The beginning of the line
                    // deal with leading whitespace
                    while (isspace(line.at(pos))) {
                        pos++;
                    }

                    for (int i = 0; i < 2; i++) {
                        // skip a token and trailing whitespace
                        while (!isspace(line.at(pos)))    // handle token
                            pos++;
                        while (isspace(line.at(pos)))    // handle whitespace
                            pos++;
                    }
                    // We are now at the beginning of the third token

                    if (line.at(pos) != '\'') {
                        // We should ge at the beginning of a string, but aren't.
                        throw("Malformed string: " + line);
                    } else {
                        pos++;    // skip the opening single quote
                    }
                    // Everything now gets copied to str until we find the closing quote.
                    // If we reach the end of the line then we have an error also.
                    while ((pos < line.length()) and (line.at(pos) != '\'')) {
                        str = str + line.at(pos++);
                    }
                    // If the string is zero length, or there was no closing
                    // delimiter, then throw an exception.
                    if (pos == line.length()    // no closing delimiter
                            or (str.length() == 0))        // zero length string
                        throw("Malformed string: " + line);
                    code_store[top].a = Memory_cell(str);
                } else {
                    // Set address or integer constant field
                    code_store[top].a = Memory_cell(stoi(tokens.at(2)));
                }
            }
        } catch (string & msg) {
            cerr << "EXCEPTION (instruction " << top << "): " << msg << endl;
            abort();
        }
    }
    last_instruction = top;
}


void open_and_load(int argc, char *argv[]) {
    // Open and load the code file. Also handles any command line flags.

    // usage of pal machine is:
    //        pal [flags] [filename]
    // If no filename is present, then the default code file named "CODE" is opened.
    // If more arguments are provided, an error is generated and the program aborts.
    // Valid flags are:
    //        -h                    Help
    //        -l                    Generate Listing (to cout)

    string code_file_name { default_code_file_name };
    bool hflag = false;        // help flag set
    bool sflag = false;        // source filename provided

    try        // Open code file.
    {
        cout << "Open files..." << endl;
        if (argc > 3) {
            // Error state. May not provide more than 2 arguments to the PAL machine.
            throw "Too many command line arguments provided.";
        } else
            for (int i = 1; i < argc; i++)
            {
                string arg = argv[i];
                if (arg == "-h")
                {
                    // Help flag. Respond to display help information. Only do this once, even if flag is set multiple times
                    if (!hflag)
                    {
                        hflag = true;    // Note that help has already been given. Once present it once
                        cout << "Usage: " << argv[0] << " [flags] [filename]" << endl;
                        cout << "    where filename is the name of the PAL file to be executed." << endl;
                        cout << endl;
                        cout << "    Valid flags are:" << endl;
                        cout << "        -h              Print out this help message." << endl;
                        cout << "        -l              Create a listing file  to standard output showing PAL code and" << endl;
                        cout << "                        and memory stack contents during the execution process." << endl;
                    }
                }
                else if (arg == "-l")
                {
                    // Generate a listing
                    debugging_pal_code = true;    // Set global flag to show that a listing is required.
                    // Name of listing file is based on the name of the source file. It is set up after the command line is processed.
                }
                else
                {
                    // no flag, so this must be the name of the source file.
                    if (!sflag)
                    {
                        sflag = true;
                        code_file_name = arg;
                    }
                    else
                        throw ("Multiple PAL source files provided");
                }
            }
        // No code file name provided. Open default file "CODE". Throw exception if
        // file does not exist and abort program.

        if (filesystem::exists(string(code_file_name)))         // Check file exists
            code_file.open(code_file_name); // Open default file for reading.
        else
            throw("File named \"" + code_file_name + "\" does not exist.");
    } catch (const string & msg) {
        cerr << "EXCEPTION: " << msg << endl;
        cerr << "usage: pal [filename]" << endl;
        abort();
    } catch (...) {
        // default exception handler. Should never fire.
        cerr << "EXCEPTION raised when opening code file." << endl;
        abort();
    }

    try // Load code file
    {
        cout << "Load code file..." << endl;
        if (!code_file.is_open()) {
            throw "Code file not open.";
        }
        if (!code_file) {
            throw "Empty code file. Execution aborts.";
        }
        load(code_file);     // read contents of code file into the code_store
        code_file.close();

        // code_store should now be populated.
    } catch (const string & msg) {
        // Exception occured when reading from code file.
        cerr << "EXCEPTION: " << msg << endl;
        abort();
    } catch (...) {
        // Exception occured when reading from code file.
        cerr << "EXCEPTION raised while reading from code file." << endl;
        abort();
    }
}


int main(int argc, char *argv[]) {
    // local variables used to measure and report elapsed time
    high_resolution_clock::time_point start;       // start time
    high_resolution_clock::time_point stop;        // stop time
    milliseconds time_span;                        // Elapsed time

    // Initialize the PAL machine
    start = high_resolution_clock::now();
    // initialize mapping of strings onto function codes.
    establish_function_mapping(); // map strings onto appropriate function codes.
    // open and load code file
    open_and_load(argc, argv);
    stop = high_resolution_clock::now();
    time_span = duration_cast < milliseconds > (stop - start);
    cout << "Time to open and load code file: " << time_span.count()
            << " milliseconds." << endl;

    // Now the code file is loaded, it's time to execute the code.
    start = high_resolution_clock::now();
    cout << endl;
    cout << "PAL-machine simulator" << endl;
    cout << "----------------------" << endl;
    cout << endl;
    execute_code();
    stop = high_resolution_clock::now();
    time_span = duration_cast < milliseconds > (stop - start);

    cout << "Execution completed in " << time_span.count() << " milliseconds."
            << endl;
    return 0;
}
