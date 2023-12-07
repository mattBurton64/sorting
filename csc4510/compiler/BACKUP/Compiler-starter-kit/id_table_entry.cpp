/*
 *  id_table_entry.cpp
 *  
 *  Last Modified: Nov 30 2023
 *  Author: Matt Burton
 *
 */

#include <string>

#include "id_table_entry.h"
#include "token.h"
#include "lille_type.h"
#include "lille_kind.h"

id_table_entry::id_table_entry() {
    id_entry = nullptr;
    lev_entry = 0;
    offset_entry = 0;
    kind_entry = lille_kind();
    trace_entry = false;
    typ_entry = lille_type();
    i_val_entry = 0;
    r_val_entry = 0.0f;
    s_val_entry = "";
    b_val_entry = false;
    p_list_entry = nullptr;
    n_par_entry = 0;
    r_ty_entry = lille_type();
}

id_table_entry::id_table_entry(token* id, lille_type typ, lille_kind kind, int level, int offset, lille_type return_tipe)
    : id_entry(id), typ_entry(typ), kind_entry(kind), lev_entry(level), offset_entry(offset), r_ty_entry(return_tipe) {
    trace_entry = false;
    i_val_entry = 0;
    r_val_entry = 0.0f;
    s_val_entry = "";
    b_val_entry = false;
    p_list_entry = nullptr;
    n_par_entry = 0;
}

void id_table_entry::trace_obj(bool trac) {
  trace_entry = trac;
}

bool id_table_entry::trace() {
  return trace_entry;
}

int id_table_entry::offset() {
    return offset_entry;
}

int id_table_entry::level() {
    return lev_entry;
}

lille_kind id_table_entry::kind() {
    return kind_entry;
}

lille_type id_table_entry::tipe() {
    return typ_entry;
}

token* id_table_entry::token_value() {
    return id_entry;
}

string id_table_entry::name() {
    return id_entry ? id_entry->get_identifier_value() : "";
}

lille_type id_table_entry::return_tipe() {
    return r_ty_entry;
}

// Getters
int id_table_entry::integer_value() const {
    return i_val_entry;
}
float id_table_entry::real_value() const {
    return i_val_entry;
}
string id_table_entry::string_value() const {
    return s_val_entry;
}
bool id_table_entry::bool_value() const {
    return b_val_entry;
}

void id_table_entry::fix_const(int integer_value, float real_value, string string_value, bool bool_value) {
    i_val_entry = integer_value;
    r_val_entry = real_value;
    s_val_entry = string_value;
    b_val_entry = bool_value;
}

void id_table_entry::fix_return_type(lille_type ret_ty) {
    r_ty_entry = ret_ty;
}

void id_table_entry::add_param(id_table_entry* param_entry) {
    if (!p_list_entry) {
        p_list_entry = param_entry;
    } else {
        id_table_entry* temp = p_list_entry;
        while (temp->p_list_entry) {
            temp = temp->p_list_entry;
        }
        temp->p_list_entry = param_entry;
    }
    n_par_entry++;
}

id_table_entry* id_table_entry::nth_parameter(int n) {
    id_table_entry* temp = p_list_entry;
    for (int i = 1; i < n; ++i) {
        if (!temp) {
            return nullptr;
        }
        temp = temp->p_list_entry;
    }
    return temp;
}

int id_table_entry::number_of_params() {
    return n_par_entry;
}

string id_table_entry::to_string() {
    string result = "Name: " + name() + "\n";
    result += "Level: " + std::to_string(level()) + "\n";
    result += "Offset: " + std::to_string(offset()) + "\n";
    result += "Kind: " + kind().to_string() + "\n";
    result += "Type: " + tipe().to_string() + "\n";
    result += "Return Type: " + return_tipe().to_string() + "\n";
    result += "Trace: " + string(trace() ? "True" : "False") + "\n";

    id_table_entry* param = p_list_entry;
    while (param != nullptr) {
      result += "Parameter: " + param->name()+ " - Type: " + param->tipe().to_string();
      param = param->p_list_entry;
    }
    
    return result;
}

