/*
 * id_table.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: Michael Oudshoorn
 */

#include <iostream>
#include <string>

#include "id_table.h"
#include "token.h"
#include "error_handler.h"
#include "id_table_entry.h"

using namespace std;

id_table::id_table(error_handler* err) {
  error = err;
  scope_level = 0;
  for (int i = 0; i < max_depth; i++) {
    sym_table[i] = nullptr;
  }
}

void id_table::enter_scope() {
  scope_level++;
}

void id_table::exit_scope() {
  sym_table[scope_level] = nullptr; // set current scope level to nullptr
  scope_level--;
}

int id_table::scope() {
  return scope_level;
}

id_table_entry* id_table::lookup(string s) {
  for (int i = 0; i <= scope_level; i++)
  {
    node* result = search_tree(s, sym_table[i]);
    if (result != nullptr)
      return result->idt;
  }
  if (debug_mode)
  {
    cout << "Id Table: lookup(s) id table entry not found" << endl;
  }
  return nullptr; // Identifier not found
}

id_table_entry* id_table::lookup(token* tok, bool for_variable) {
  if (tok != nullptr) {
    string identifier_name = tok->get_identifier_value(); // Get the identifier name from the token
    id_table_entry* result = lookup(identifier_name);
    if (result != nullptr)
    {
      if (debug_mode)
        cout << "Id Table: lookup(tok) id table entry found" << endl;

      return result;
    }
  }
  if (!for_variable) error->flag(tok, 81); //Identifier not previously declared.
  if (debug_mode)
  {
    cout << "Id Table: lookup(tok) id table entry not found" << endl;
  }
  // if the token is not in the table, add it
  lille_type ty;
  if (tok->get_sym() == symbol::integer)
    ty = lille_type::type_integer;
  else if (tok->get_sym() == symbol::real_num)
    ty = lille_type::type_real;
  else if (tok->get_sym() == symbol::strng)
    ty = lille_type::type_string;
  else if (tok->get_sym() == symbol::true_sym or tok->get_sym() == symbol::false_sym)
    ty = lille_type::type_boolean;

  return enter_id(tok, ty, for_variable ? lille_kind::constant : lille_kind::variable, scope_level, 0, lille_type::type_unknown);
  //return nullptr; // Token not found
}

void id_table::trace_all(bool b) {
  debug_mode = b;
}

bool id_table::trace_all() {
  return debug_mode;
}

void id_table::add_table_entry(id_table_entry* id) {
  if (scope_level < max_depth) {
    add_table_entry(id, &sym_table[scope_level]);
  } else {
    error->flag(id->token_value(), 130);  // Handle error: Exceeded maximum scope depth
  }
}

id_table_entry* id_table::enter_id(token* id, lille_type typ, lille_kind kind, int level, int offset, lille_type return_tipe) {
  id_table_entry* id_entry = new id_table_entry(id, typ, kind, level, offset, return_tipe);
  add_table_entry(id_entry);
  return id_entry;
}

void id_table::dump_id_table(bool dump_all) {
  if (!dump_all) {
    cout << "Identifiers (Scope " << scope_level << "):" << endl;
    dump_all_identifiers(sym_table[scope_level]);
    cout << endl;
  }
  else {
    for (int i = 0; i <= scope_level; ++i) {
      cout << "Symbol Table (Scope " << i << "):" << endl;
      dump_tree(sym_table[i]);
      cout << endl;
    }
  }
}

id_table::node* id_table::search_tree(string s, node* p) {
  if (p == nullptr || p->idt->name() == s)
    return p;

  if (s < p->idt->name())
    return search_tree(s, p->left);
    
  return search_tree(s, p->right);
}

void id_table::add_table_entry(id_table_entry* it, node** ptr) {
  if (*ptr == nullptr) {
    *ptr = new node;
    (*ptr)->idt = it;
    (*ptr)->left = nullptr;
    (*ptr)->right = nullptr;
  } else if (it->name() < (*ptr)->idt->name()) {
    add_table_entry(it, &((*ptr)->left));
  } else if (it->name() > (*ptr)->idt->name()) {
    add_table_entry(it, &((*ptr)->right));
  } else {
    if (it->name() != "INT2REAL" and it->name() != "REAL2INT" and it->name() != "INT2STRING" and it->name() != "REAL2STRING" and it->name() != "READ" and it->name() != "WRITE" and it->name() != "WRITELN")
      error->flag(it->token_value(), 82); //Identifier declared multiple times in same block
  }
}

void id_table::dump_tree(node* ptr) {
  if (ptr != nullptr) {
    dump_tree(ptr->left);
    cout << ptr->idt->to_string() << endl;
    dump_tree(ptr->right);
  }
}

void id_table::dump_all_identifiers(node* ptr) {
  if (ptr != nullptr) {
    dump_all_identifiers(ptr->left);
    cout << "Identifier: " << ptr->idt->name() << " - Type: " << ptr->idt->tipe().to_string() << endl;
    dump_all_identifiers(ptr->right);
  }
}
