#include "database.h"
#include <stdlib.h>
#include <stdio.h>

t_encrypted_database *database_from_path(char *concp_path) {
  // TODO: implement
	return NULL;
}

t_decrypted_database *decrypt_database(t_encrypted_database *t_enc_db, char *concp_password) {
  // TODO: implement
	return NULL;
}

int close_decrypted_database(t_decrypted_database *t_dec_db) {
  // TODO: implement
	return 1;
}

int close_encrypted_database(t_encrypted_database *t_enc_db) {
  // TODO: implement
	return 1;
}
