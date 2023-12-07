/*
 * idtable.h
 *
 *  Created on: Jun 18, 2020
 *      Author: Michael Oudshoorn
 */

#ifndef ID_TABLE_H
#define ID_TABLE_H

#include "error_handler.h"
#include "id_table_entry.h"
#include "lille_type.h"
#include "lille_kind.h"
#include "token.h"

class id_table {
public:
    id_table(error_handler* err);

    void enter_scope();
    void exit_scope();
    int scope();
    id_table_entry* lookup(std::string s);
    id_table_entry* lookup(token* tok, bool for_variable);
    void trace_all(bool b);
    bool trace_all();
    void add_table_entry(id_table_entry* id);
    id_table_entry* enter_id(token* id, lille_type typ, lille_kind kind, int level, int offset, lille_type return_tipe);
    void dump_id_table(bool dump_all = true);

private:
    static const int max_depth = 1000; // Assuming a maximum depth of the symbol table
    struct node {
        id_table_entry* idt;
        node* left;
        node* right;
    };

    error_handler* error;
    bool debug_mode = {false};
    int scope_level;
    node* sym_table[max_depth];

    node* search_tree(std::string s, node* p);
    void add_table_entry(id_table_entry* it, node** ptr);
    void dump_tree(node* ptr);
    void dump_all_identifiers(node* ptr);
};

#endif // ID_TABLE_H

