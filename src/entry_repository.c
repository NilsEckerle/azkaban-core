#include "entry_repository.h"

t_entry *get_entry(t_decrypted_database *t_ddb_db, int i_id) {
    return NULL;
}

t_entry *search_entry(t_decrypted_database *t_ddb_db, char *cp_search_name) {
    return NULL;
}

t_linked_list_node *get_entry_list(t_decrypted_database *t_ddb_db) {
    return NULL;
}

int create_entry(t_decrypted_database *t_ddb_db, t_entry *t_new_entry) {
    return 1;
}

int delete_entry(t_decrypted_database *t_ddb_db, int i_id) {
    return 1;
}

int delete_entry_hard(t_decrypted_database *t_ddb_db, int i_id) {
    return 1;
}

int change_entry(t_decrypted_database *t_ddb_db, int i_old_id, t_entry *t_new_entry) {
    return 1;
}

int setup_table_entry(t_decrypted_database *t_ddb_db) {
    const char *create_table_sql = 
        "CREATE TABLE entry ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL, "
        "user_name TEXT NOT NULL, "
        "password TEXT NOT NULL, "
        "is_deleted INTEGER"
        ");";
    int rc = sqlite3_exec(t_ddb_db->sql3p_database, create_table_sql, NULL, NULL, NULL);
    return rc;
}
