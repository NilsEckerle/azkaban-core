#include "database.h"
#include "sqlite3.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_FILE_PATH "unit_testing_scrap_database.azk"

void test_decrypt_database() {
  // setup - manually create encrypted database structure
  t_encrypted_database *t_enc_db = malloc(sizeof(t_encrypted_database));
  assert(t_enc_db != NULL);

  // Create a test database file
  FILE *file = fopen(TEST_FILE_PATH, "r");
  if (file != NULL) {
    fclose(file);
    assert(remove(TEST_FILE_PATH) == 0);
  }

  // Create and open SQLite database manually
  int rc = sqlite3_open(TEST_FILE_PATH, &t_enc_db->sql3p_database);
  assert(rc == SQLITE_OK);
  assert(t_enc_db->sql3p_database != NULL);

  // TEST: decrypt_database()
  t_decrypted_database *t_dec_db = decrypt_database(t_enc_db, "Test123");

  // Verify function worked
  assert(t_dec_db != NULL);
  assert(t_dec_db->sql3p_database != NULL);

  // Test that we can use the decrypted database
  const char *create_table_sql = "CREATE TABLE test_table (id INTEGER PRIMARY KEY, name TEXT);";
  rc = sqlite3_exec(t_dec_db->sql3p_database, create_table_sql, NULL, NULL, NULL);
  assert(rc == SQLITE_OK);

  // Test with wrong password (should return NULL)
  t_encrypted_database *t_enc_db2 = malloc(sizeof(t_encrypted_database));
  rc = sqlite3_open(TEST_FILE_PATH, &t_enc_db2->sql3p_database);
  assert(rc == SQLITE_OK);

  t_decrypted_database *null_db = decrypt_database(t_enc_db2, "WrongPassword");
  assert(null_db == NULL);

  // Manual cleanup
  if (t_dec_db->sql3p_database) {
    sqlite3_close(t_dec_db->sql3p_database);
  }
  free(t_dec_db);

  if (t_enc_db->sql3p_database) {
    sqlite3_close(t_enc_db->sql3p_database);
  }
  free(t_enc_db);

  if (t_enc_db2->sql3p_database) {
    sqlite3_close(t_enc_db2->sql3p_database);
  }
  free(t_enc_db2);

  remove(TEST_FILE_PATH);

  printf("test_decrypt_database passed\n");
}

int main() {
  printf("Running test_decrypt_database...\n");
  test_decrypt_database();
  printf("test_decrypt_database passed successfully!\n");
  return 0;
}
