/*
 * Memory_cell.cpp
 *
 Author:     Michael Oudshoorn
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

#include "Memory_cell.h"

Memory_cell::Memory_cell()         // undefined memory cell, types set to types_UNDEF
{
    set_undef();
}

Memory_cell::Memory_cell(bool b) // boolean memory cell, types set to types_BOOLEAN
{
    set_boolean(b);
}

Memory_cell::Memory_cell(int i) // integer memory cell, types set to types_INT
{
    set_int(i);
}

Memory_cell::Memory_cell(float f) // real/float memory cell, types set to types_REAL
{
    set_real(f);
}

Memory_cell::Memory_cell(string s) // string memory cell, types set to types_STRING
{
    set_string(s);
}

bool Memory_cell::is_undef()            // Returns true if memory cell has type types_UNDEF
{
    return (this->type == types_UNDEF);
}

bool Memory_cell::is_boolean()        // Returns true if memory cell has type type_BOOLEAN
{
    return (this->type == types_BOOLEAN);
}

bool Memory_cell::is_int()            // Returns true if memory cell has type types_INT
{
    return (this->type == types_INT);
}

bool Memory_cell::is_real()            // Returns true if memory cell has type types_REAL
{
    return (this->type == types_REAL);
}

bool Memory_cell::is_string()        // Returns true if memory cell has type types_STRING
{
    return (this->type == types_STRING);
}

void Memory_cell::set_boolean(bool b) // boolean memory cell, types set to types_BOOLEAN
{
    this->type = types_BOOLEAN;
    this->bvalue = b;
}

void Memory_cell::set_int(int i)        // integer memory cell, types set to types_INT
{
    this->type = types_INT;
    this->ivalue = i;
}

void Memory_cell::set_real(float f)     // real/float memory cell, types set to types_REAL
{
    this->type = types_REAL;
    this->rvalue = f;
}

void Memory_cell::set_string(string s) // string memory cell, types set to types_STRING
{
    this->type = types_STRING;
    this->svalue = s;
}

void Memory_cell::set_undef()            // sets the memory cell to be undefined.
{
    this->type = types_UNDEF;
}

Memory_cell::types Memory_cell::get_type()    // returns the type of memory cell
{
    return this->type;
}

bool Memory_cell::get_boolean()    // returns boolean value in cell if types is types_BOOLEAN, otherwise
                                // throws an exception.
{
    if (this->type == types_BOOLEAN)
        return this->bvalue;
    else
        throw "Illegal access of value in memory cell";
}

int Memory_cell::get_int()        // returns integer value in cell if types is types_INTEGER, otherwise
                                // throws an exception.
{
    if (this->type == types_INT)
        return this->ivalue;
    else
        throw "Illegal access of value in memory cell";
}

float Memory_cell::get_real()    // returns real/float value in cell if types is types_REAL, otherwise
                                // throws an exception.
{
    if (this->type == types_REAL)
        return this->rvalue;
    else
        throw "Illegal access of value in memory cell";
}

string Memory_cell::get_string()    // returns string value in cell if types is types_STRING, otherwise
                                    // throws an exception.
{
    if (this->type == types_STRING)
        return this->svalue;
    else
        throw "Illegal access of value in memory cell";
}

string Memory_cell::to_string()        // Return string representing the memory cell
{
    string s { "" };

    if (this->is_undef())
        s = "UNDEF   ";
    else if (this->is_boolean())
        s = "BOOLEAN " + std::to_string(this->get_boolean());
    else if (this->is_int())
        s = "INT     " + std::to_string(this->get_int());
    else if (this->is_real())
        s = "REAL    " + std::to_string(this->get_real());
    else if (this->is_string())
        s = "STRING  " + this->get_string();
    return s;
}


