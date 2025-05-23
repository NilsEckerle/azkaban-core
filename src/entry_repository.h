#ifndef ENTRY_REPOSITORY_H
#define ENTRY_REPOSITORY_H

#include "linked_list.h"
#include "entry.h"
#include "database.h"

t_entry *fn_get_entry(t_decrypted_database *t_ddb_db, int i_id);

t_entry *fn_search_entry(t_decrypted_database *t_ddb_db, char *cp_search_name);

t_linked_list_node *fn_get_entry_list(t_decrypted_database *t_ddb_db);

int fn_create_entry(t_decrypted_database *t_ddb_db, t_entry *t_new_entry);

int fn_delete_entry(t_decrypted_database *t_ddb_db, int i_id);

int fn_delete_entry_hard(t_decrypted_database *t_ddb_db, int i_id);

int fn_change_entry(t_decrypted_database *t_ddb_db, int i_old_id, t_entry *t_new_entry);

int fn_setup_table(t_decrypted_database *t_ddb_db);

#endif
