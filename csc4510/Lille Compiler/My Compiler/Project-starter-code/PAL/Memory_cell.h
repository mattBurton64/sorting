/*
 * Memory_cell.h
 *
 * Author:     Michael Oudshoorn
 *             Webb School of Engineering
 *             High Point University
 *             High Point
 *             NC   27265
 *             USA
 *
 * Written:            1 May 2020
 * Last modified:     1 May 2020
 *
 * Open Source - free to distribute and modify. May not be used for profit.
 *
 */

#ifndef MEMORY_CELL_H_
#define MEMORY_CELL_H_

#include <string>

using namespace std;

class Memory_cell {
    // The PAL machine uses a tagged architecture whereby each memory location contains
    // a value and the type associated with that value. This prevents types from being used
    // or accessed inappropriately and is done deliberately to make life a little easier
    // for students writing their compiler. This is a class  that would need to be modified
    // if you choose to simply store a bit pattern in each memory cell and want to be able to
    // do things such as write a floating point number to a cell and then interpret it as an
    // integer.

public:

    enum types            // Types known to the PAL machine
    {
        types_UNDEF,    // Undefined
        types_BOOLEAN,    // Boolean
        types_INT,        // Integer
        types_REAL,        // Real or float
        types_STRING    // String
    };

    // Constructors. There is one for each type of tagged storage.
    Memory_cell();            // undefined memory cell, types set to types_UNDEF

    Memory_cell(bool b);    // boolean memory cell, types set to types_BOOLEAN

    Memory_cell(int i);        // integer memory cell, types set to types_INT

    Memory_cell(float f);    // real/float memory cell, types set to types_REAL

    Memory_cell(string s);    // string memory cell, types set to types_STRING

    bool is_undef();        // Returns true if memory cell has type types_UNDEF

    bool is_boolean();        // Returns true if memory cell has type type_BOOLEAN

    bool is_int();            // Returns true if memory cell has type types_INT

    bool is_real();            // Returns true if memory cell has type types_REAL

    bool is_string();        // Returns true if memory cell has type types_STRING

    void set_boolean(bool b);    // boolean memory cell, types set to types_BOOLEAN

    void set_int(int i);    // integer memory cell, types set to types_INT

    void set_real(float f); // real/float memory cell, types set to types_REAL

    void set_string(string s);    // string memory cell, types set to types_STRING

    void set_undef();        // sets the memory cell to be undefined.

    types get_type();        // returns the type of memory cell

    bool get_boolean();        // returns boolean value in cell if types is types_BOOLEAN, otherwise
                            // throws an exception.

    int get_int();            // returns integer value in cell if types is types_INTEGER, otherwise
                                // throws an exception.

    float get_real();        // returns real/float value in cell if types is types_REAL, otherwise
                             // throws an exception.

    string get_string();    // returns string value in cell if types is types_STRING, otherwise
                            // throws an exception.

    string to_string();        // Return string representing the memory cell

private:
    // type will record the the type of value stored in the memory cell
    // Based on this value, only one of the resulting values will be accessible.
    types type { types_UNDEF };    // Type of value stored in the memory cell
    bool bvalue { false };        // Boolean value in cell if type == types_BOOLELAN
    int ivalue { 0 };            // Integer value in cell is type == types_INT
    float rvalue { 0.0 };          // Real (float) value in cell if type == types_REAL
    string svalue { "" };          // String value in cell if type == types_STRING
};

#endif /* MEMORY_CELL_H_ */
