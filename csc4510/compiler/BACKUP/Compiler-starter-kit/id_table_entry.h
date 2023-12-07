/*
 * id_table_entry.h
 *
 *  Created on: Nov 30, 2023
 *      Author: Matt Burton
 */

#ifndef ID_TABLE_ENTRY_H
#define ID_TABLE_ENTRY_H

#include <string>
#include "token.h"
#include "lille_type.h"
#include "lille_kind.h"

class id_table_entry {
public:
    id_table_entry();
    id_table_entry(token* id, lille_type typ, lille_kind kind, int level, int offset, lille_type return_tipe);

    void trace_obj(bool trac);
    bool trace();
    int offset();
    int level();
    lille_kind kind();
    lille_type tipe();
    token* token_value();
    string name();
    int integer_value() const;
    float real_value() const;
    std::string string_value() const;
    bool bool_value() const;
    lille_type return_tipe();
    void fix_const(int integer_value, float real_value, std::string string_value, bool bool_value);
    void fix_return_type(lille_type ret_ty);
    void add_param(id_table_entry* param_entry);
    id_table_entry* nth_parameter(int n);
    int number_of_params();
    std::string to_string();

private:
    token* id_entry;
    int lev_entry;
    int offset_entry;
    lille_kind kind_entry;
    bool trace_entry;
    lille_type typ_entry;
    int i_val_entry;
    float r_val_entry;
    std::string s_val_entry;
    bool b_val_entry;
    id_table_entry* p_list_entry;
    int n_par_entry;
    lille_type r_ty_entry;
};

#endif /* ID_TABLE_ENTRY_H */

