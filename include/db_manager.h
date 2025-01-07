/**
 * @file db_manager.h
 * @brief Database management functions for Azkaban Core.
 * 
 * This header provides the API for managing SQLite databases,
 * including CRUD operations for entries, entry details, and folders.
 * It also includes encryption and setup utilities.
 */

#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#define SQLITE_HAS_CODEC
#include "entry.h"
#include <sqlcipher/sqlite3.h>

/**
 * @brief Closes the database connection.
 * @param db Pointer to the SQLite database connection.
 */
void db_close(sqlite3 *db);

/**
 * @brief Opens a database connection with a password.
 * @param filename Path to the database file.
 * @param password Password for database encryption.
 * @return Pointer to the opened SQLite database.
 */
sqlite3 *db_open(const char *filename, const char *password);

/**
 * @brief Creates a table in the database. For internal use.
 * @param db Pointer to the SQLite database connection.
 * @param sql_statement SQL statement to create the table.
 */
void _db_create_table(sqlite3 *db, const char *sql_statement);

/**
 * @brief Sets up the initial database schema. For internal use
 * @param db Pointer to the SQLite database connection.
 */
void _db_setup(sqlite3 *db);

/**
 * @brief Retrieves all entries from the database without password.
 * @param db Pointer to the SQLite database connection.
 * @return Pointer to a linked list of EntryNode structures.
 */
EntryNode *db_get_all_entries(sqlite3 *db);

/**
 * @brief Retrieves a single entry by name without password.
 * @param db Pointer to the SQLite database connection.
 * @param name Name of the entry.
 * @return Pointer to an Entry structure.
 */
Entry *db_get_entry(sqlite3 *db, char *name);

/**
 * @brief Retrieves all details of an entry.
 * @param db Pointer to the SQLite database connection.
 * @param from_entry_id ID of the entry.
 * @return Pointer to a linked list of EntryDetailNode structures.
 */
EntryDetailNode *db_get_all_entryDetail(sqlite3 *db, int from_entry_id);

/**
 * @brief Retrieves the password for a specific entry.
 * @param db Pointer to the SQLite database connection.
 * @param id ID of the entry.
 * @return Password as a string.
 */
const char *db_get_password(sqlite3 *db, int id);

/**
 * @brief Updates an existing entry in the database.
 * 
 * @param db Pointer to the SQLite database connection.
 * @param entry_id ID of the entry to update.
 * @param new_entry Struct containing updated entry data.
 * @return 0 on success, non-zero on failure.
 */
int db_change_entry(sqlite3 *db, int entry_id, Entry new_entry);

/**
 * @brief Updates an existing entry detail in the database.
 * 
 * @param db Pointer to the SQLite database connection.
 * @param id ID of the entry detail to update.
 * @param new_entry_detail Struct containing updated entry detail data.
 * @return 0 on success, non-zero on failure.
 */
int db_change_entryDetail(sqlite3 *db, int id, EntryDetail new_entry_detail);

/**
 * @brief Writes a new entry into the database.
 * 
 * @param db Pointer to the SQLite database connection.
 * @param entry Struct containing the entry data.
 * @return 0 on success, non-zero on failure.
 */
int db_write_entry(sqlite3 *db, Entry entry);

/**
 * @brief Writes a new entry detail into the database.
 * 
 * @param db Pointer to the SQLite database connection.
 * @param entry_detail Struct containing the entry detail data.
 * @return 0 on success, non-zero on failure.
 */
int db_write_entryDetail(sqlite3 *db, EntryDetail entry_detail);

/**
 * @brief Deletes an entry from the database.
 * 
 * @param db Pointer to the SQLite database connection.
 * @param entry_id ID of the entry to delete.
 * @return 0 on success, non-zero on failure.
 */
int db_delete_entry(sqlite3 *db, int entry_id);

/**
 * @brief Deletes an entry detail from the database.
 * 
 * @param db Pointer to the SQLite database connection.
 * @param entry_detail_id ID of the entry detail to delete.
 * @return 0 on success, non-zero on failure.
 */
int db_delete_entryDetail(sqlite3 *db, int entry_detail_id);

/**
 * @brief Adds an entry to a specific folder in the database.
 * 
 * @param db Pointer to the SQLite database connection.
 * @param entry_id ID of the entry to add.
 * @param folder_name Name of the folder.
 * @return 0 on success, non-zero on failure.
 */
int db_add_to_folder(sqlite3 *db, int entry_id, char *folder_name);

/**
 * @brief Retrieves all folders from the database.
 * 
 * @param db Pointer to the SQLite database connection.
 * @return Pointer to a linked list of FolderNode structures.
 */
FolderNode *db_get_all_folder(sqlite3 *db);

/**
 * @brief Retrieves entries from a specific folder.
 * 
 * @param db Pointer to the SQLite database connection.
 * @param folder_name Name of the folder.
 * @return Pointer to a linked list of FolderNode structures containing the folder's entries.
 */
FolderNode *db_get_from_folder(sqlite3 *db, char *folder_name);

/**
 * @brief Decrypts the database using the provided password.
 * 
 * @param db Pointer to the SQLite database connection.
 * @param password Password used for decryption.
 */
void _db_decrypt(sqlite3 *db, const char *password);

#endif
