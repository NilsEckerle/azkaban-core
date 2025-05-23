#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"

/**
 * @struct st_decrypted_database
 * @brief Structure representing a decrypted database connection.
 */
typedef struct st_decrypted_database {
	sqlite3 *sql3p_database; /**< SQLite database handle for decrypted access. */
} t_decrypted_database;

/**
 * @struct st_encrypted_database
 * @brief Structure representing an encrypted database connection.
 */
typedef struct st_encrypted_database {
	sqlite3 *sql3p_database; /**< SQLite database handle for encrypted access. */
} t_encrypted_database;

/**
 * @brief Opens an encrypted database from file path.
 * @param concp_path - Path to the database file.
 * @return - Pointer to encrypted database structure if successful, NULL otherwise.
 */
t_encrypted_database *database_from_path(char *concp_path);

/**
 * @brief Decrypts an encrypted database using the provided password.
 * @param t_enc_db - Pointer to the encrypted database structure.
 * @param concp_password - Password string for decryption.
 * @return - Pointer to decrypted database structure if successful, NULL otherwise.
 * @note After successful decryption, the encrypted database's SQLite handle is set to NULL.
 */
t_decrypted_database *decrypt_database(t_encrypted_database *t_enc_db, char *concp_password);

/**
 * @brief Closes a decrypted database connection and encrypts the data.
 * @param t_dec_db - Pointer to the decrypted database structure.
 * @return - 0 if successful, non-zero otherwise.
 * @note After closing, the database's SQLite handle is set to NULL.
 */
int close_decrypted_database(t_decrypted_database *t_dec_db);

/**
 * @brief Closes an encrypted database connection.
 * @param t_enc_db - Pointer to the encrypted database structure.
 * @return - 0 if successful, non-zero otherwise.
 * @note After closing, the database's SQLite handle is set to NULL.
 */
int close_encrypted_database(t_encrypted_database *t_enc_db);

#endif
