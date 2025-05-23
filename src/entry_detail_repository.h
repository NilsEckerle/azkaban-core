#ifndef ENTRY_DETAIL_REPOSITORY_H
#define ENTRY_DETAIL_REPOSITORY_H

#include "linked_list.h"
#include "entry_detail.h"
#include "database.h"

/**
 * @brief Retrieves an entry detail by its unique ID.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param i_id - Unique identifier of the entry detail to retrieve.
 * @return - Pointer to the entry detail structure if found, NULL otherwise.
 */
t_entry_detail *get_entry_detail_detail(t_decrypted_database *t_ddb_db, int i_id);

/**
 * @brief Searches for an entry detail by associated entry name.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param cp_search_name - Name string to search for in associated entries.
 * @return - Pointer to the first matching entry detail structure if found, NULL otherwise.
 * @note This function searches entry details based on their associated entry's name.
 */
t_entry_detail *search_entry_detail_detail(t_decrypted_database *t_ddb_db, char *cp_search_name);

/**
 * @brief Retrieves all entry details from the database as a linked list.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @return - Pointer to the head of a linked list containing all entry details, NULL if empty or on error.
 * @note The returned list contains pointers to t_entry_detail structures in the vp_data field of each node.
 */
t_linked_list_node *get_entry_detail_detail_list(t_decrypted_database *t_ddb_db);

/**
 * @brief Creates a new entry detail in the database.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param t_new_entry_detail - Pointer to the entry detail structure to be created.
 * @return - 0 if successful, non-zero otherwise.
 * @note The entry detail's ID may be modified after creation to reflect the database-assigned ID.
 */
int create_entry_detail(t_decrypted_database *t_ddb_db, t_entry_detail *t_new_entry_detail);

/**
 * @brief Soft deletes an entry detail by setting its deletion flag.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param i_id - Unique identifier of the entry detail to delete.
 * @return - 0 if successful, non-zero otherwise.
 * @note This performs a soft delete by setting b_is_deleted to 1.
 */
int delete_entry_detail(t_decrypted_database *t_ddb_db, int i_id);

/**
 * @brief Permanently removes an entry detail from the database.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param i_id - Unique identifier of the entry detail to permanently delete.
 * @return - 0 if successful, non-zero otherwise.
 * @note This performs a hard delete, completely removing the entry detail from the database.
 */
int delete_entry_detail_hard(t_decrypted_database *t_ddb_db, int i_id);

/**
 * @brief Updates an existing entry detail with new data.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @param i_old_id - Unique identifier of the entry detail to update.
 * @param t_new_entry_detail - Pointer to the entry detail structure containing updated data.
 * @return - 0 if successful, non-zero otherwise.
 */
int change_entry_detail(t_decrypted_database *t_ddb_db, int i_old_id, t_entry_detail *t_new_entry_detail);

/**
 * @brief Sets up the entry detail table in the database.
 * @param t_ddb_db - Pointer to the decrypted database connection.
 * @return - 0 on success, 1 on generic failure, 2 if table already exists.
 * @note This function creates the necessary table structure for storing entry details.
 */
int setup_table_entry_detail(t_decrypted_database *t_ddb_db);

#endif // !ENTRY_DETAIL_REPOSITORY_H
