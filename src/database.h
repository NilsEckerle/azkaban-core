#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"

typedef struct stDecryptedDatabase {
	sqlite3 *sqlDatabase;
} stDecryptedDatabase;

typedef struct stEncryptedDatabase {
	sqlite3 *sqlDatabase;
} stEncryptedDatabase;

stEncryptedDatabase fnDatabaseFromPath(const char *cocpPath);

stDecryptedDatabase fnDecryptDatabase(stEncryptedDatabase stEncrypted, char *password);

int fnCloseDatabase(stDecryptedDatabase *stDecrypted);

#endif
