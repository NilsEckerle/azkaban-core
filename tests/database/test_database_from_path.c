#include "database.h"
#include "sqlite3.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_FILE_PATH "unit_testing_scrap_database.azk"

void test_database_from_path() {
  // setup - create test file
  FILE *file = fopen(TEST_FILE_PATH, "r");
  if (file != NULL) {
    fclose(file);
    assert(remove(TEST_FILE_PATH) == 0);
  }

  file = fopen(TEST_FILE_PATH, "w");
  assert(file != NULL);
  fclose(file);

  // TEST: database_from_path()
  t_encrypted_database *t_enc_db = database_from_path(TEST_FILE_PATH);

  // Verify function worked
  assert(t_enc_db != NULL);
  assert(t_enc_db->sql3p_database != NULL);

  // Test with non-existent file (should return NULL)
  t_encrypted_database *null_db = database_from_path("non_existent_file.azk");
  assert(null_db == NULL);

  // Manual cleanup (don't use close_encrypted_database - we're not testing that)
  sqlite3_close(t_enc_db->sql3p_database);
  free(t_enc_db);

  // cleanup test file
  remove(TEST_FILE_PATH);

  printf("test_database_from_path passed\n");
}

int main() {
  printf("Running test_database_from_path...\n");
  test_database_from_path();
  printf("test_database_from_path passed successfully!\n");
  return 0;
}
