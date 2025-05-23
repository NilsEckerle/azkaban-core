#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"

typedef struct st_decrypted_database {
	sqlite3 *sql3p_database;
} t_decrypted_database;

typedef struct st_encrypted_database {
	sqlite3 *sql3p_database;
} t_encrypted_database;

t_encrypted_database database_from_path(const char *concp_path);

t_decrypted_database decrypt_database(t_encrypted_database tedb_db, const char *concp_password);

int close_database(t_decrypted_database *tddb_db);

#endif
