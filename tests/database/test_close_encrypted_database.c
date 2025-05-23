#include "database.h"
#include "sqlite3.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_FILE_PATH "unit_testing_scrap_database.azk"

void test_close_encrypted_database() {
  // setup - manually create encrypted database structure
  t_encrypted_database *t_enc_db = malloc(sizeof(t_encrypted_database));
  assert(t_enc_db != NULL);

  // Create test database file
  FILE *file = fopen(TEST_FILE_PATH, "w");
  assert(file != NULL);
  fclose(file);

  // Open SQLite database manually
  int rc = sqlite3_open(TEST_FILE_PATH, &t_enc_db->sql3p_database);
  assert(rc == SQLITE_OK);
  assert(t_enc_db->sql3p_database != NULL);

  // TEST: close_encrypted_database()
  int result = close_encrypted_database(t_enc_db);

  // Verify function worked
  assert(result == 0);                      // assuming 0 means success
  assert(t_enc_db->sql3p_database == NULL); // should be set to NULL

  // Test calling on already closed database (should handle gracefully)
  int result2 = close_encrypted_database(t_enc_db);
  assert(result2 == 0); // should still return success
  assert(t_enc_db->sql3p_database == NULL);

  // Test with NULL pointer (should handle gracefully)
  int result3 = close_encrypted_database(NULL);
  assert(result3 != 0); // should return error code

  // Manual cleanup
  free(t_enc_db);
  remove(TEST_FILE_PATH);

  printf("test_close_encrypted_database passed\n");
}

int main() {
  printf("Running test_close_encrypted_database...\n");
  test_close_encrypted_database();
  printf("test_close_encrypted_database passed successfully!\n");
  return 0;
}
