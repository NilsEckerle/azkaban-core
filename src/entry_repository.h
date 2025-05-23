#ifndef ENTRY_REPOSITORY_H
#define ENTRY_REPOSITORY_H

#include "linked_list.h"
#include "entry.h"
#include "database.h"

/**
 * @brief Retrieves an entry by its unique ID.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param i_id - Unique identifier of the entry to retrieve.
 * @return - Pointer to the entry structure if found, NULL otherwise.
 */
t_entry *get_entry(t_decrypted_database *t_ddb_db, int i_id);

/**
 * @brief Searches for an entry by name.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param cp_search_name - Name string to search for.
 * @return - Pointer to the first matching entry structure if found, NULL otherwise.
 */
t_entry *search_entry(t_decrypted_database *t_ddb_db, char *cp_search_name);

/**
 * @brief Retrieves all entries from the database as a linked list.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @return - Pointer to the head of a linked list containing all entries, NULL if empty or on error.
 * @note The returned list contains pointers to t_entry structures in the vp_data field of each node.
 */
t_linked_list_node *get_entry_list(t_decrypted_database *t_ddb_db);

/**
 * @brief Creates a new entry in the database.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param t_new_entry - Pointer to the entry structure to be created.
 * @return - 0 if successful, non-zero otherwise.
 * @note The entry's ID may be modified after creation to reflect the database-assigned ID.
 */
int create_entry(t_decrypted_database *t_ddb_db, t_entry *t_new_entry);

/**
 * @brief Soft deletes an entry by setting its deletion flag.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param i_id - Unique identifier of the entry to delete.
 * @return - 0 if successful, non-zero otherwise.
 * @note This performs a soft delete by setting b_is_deleted to 1.
 */
int delete_entry(t_decrypted_database *t_ddb_db, int i_id);

/**
 * @brief Permanently removes an entry from the database.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param i_id - Unique identifier of the entry to permanently delete.
 * @return - 0 if successful, non-zero otherwise.
 * @note This performs a hard delete, completely removing the entry from the database.
 */
int delete_entry_hard(t_decrypted_database *t_ddb_db, int i_id);

/**
 * @brief Updates an existing entry with new data.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param i_old_id - Unique identifier of the entry to update.
 * @param t_new_entry - Pointer to the entry structure containing updated data.
 * @return - 0 if successful, non-zero otherwise.
 */
int change_entry(t_decrypted_database *t_ddb_db, int i_old_id, t_entry *t_new_entry);

/**
 * @brief Sets up the entry table in the database.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @return - 0 on success, sqlite3 return code otherwise
 * @note This function creates the necessary table structure for storing entries.
 */
int setup_table_entry(t_decrypted_database *t_ddb_db);

#endif
