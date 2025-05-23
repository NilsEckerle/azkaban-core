#include "database.h"
#include "sqlite3.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_FILE_PATH "unit_testing_scrap_database.azk"

void test_close_decrypted_database() {
  // setup - manually create decrypted database structure
  t_decrypted_database *t_dec_db = malloc(sizeof(t_decrypted_database));
  assert(t_dec_db != NULL);

  // Create test database file
  FILE *file = fopen(TEST_FILE_PATH, "w");
  assert(file != NULL);
  fclose(file);

  // Open SQLite database manually
  int rc = sqlite3_open(TEST_FILE_PATH, &t_dec_db->sql3p_database);
  assert(rc == SQLITE_OK);
  assert(t_dec_db->sql3p_database != NULL);

  // Add some test data to verify encryption works
  const char *create_table_sql = "CREATE TABLE test_table (id INTEGER PRIMARY KEY, data TEXT);";
  rc = sqlite3_exec(t_dec_db->sql3p_database, create_table_sql, NULL, NULL, NULL);
  assert(rc == SQLITE_OK);

  const char *insert_sql = "INSERT INTO test_table (data) VALUES ('secret_data');";
  rc = sqlite3_exec(t_dec_db->sql3p_database, insert_sql, NULL, NULL, NULL);
  assert(rc == SQLITE_OK);

  // TEST: close_decrypted_database()
  int result = close_decrypted_database(t_dec_db);

  // Verify function worked
  assert(result == 0);                      // assuming 0 means success
  assert(t_dec_db->sql3p_database == NULL); // should be set to NULL

  // Verify data is encrypted by trying to read it with raw SQLite
  sqlite3 *raw_db;
  rc = sqlite3_open(TEST_FILE_PATH, &raw_db);
  assert(rc == SQLITE_OK);

  sqlite3_stmt *stmt;
  const char *select_sql = "SELECT data FROM test_table WHERE id = 1;";
  rc = sqlite3_prepare_v2(raw_db, select_sql, -1, &stmt, NULL);
  if (rc == SQLITE_OK) {
    rc = sqlite3_step(stmt);
    // Should fail to read data due to encryption
    assert(rc != SQLITE_ROW);
    sqlite3_finalize(stmt);
  }
  sqlite3_close(raw_db);

  // Test calling on already closed database
  int result2 = close_decrypted_database(t_dec_db);
  assert(result2 == 0); // should handle gracefully

  // Test with NULL pointer
  int result3 = close_decrypted_database(NULL);
  assert(result3 != 0); // should return error code

  // Manual cleanup
  free(t_dec_db);
  remove(TEST_FILE_PATH);

  printf("test_close_decrypted_database passed\n");
}

int main() {
  printf("Running test_close_decrypted_database...\n");
  test_close_decrypted_database();
  printf("test_close_decrypted_database passed successfully!\n");
  return 0;
}
