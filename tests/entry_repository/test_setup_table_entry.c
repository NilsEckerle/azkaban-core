#include "database.h"
#include "entry_repository.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_FILE_PATH "unit_testing_setup_table_entry.azk"
#define TEST_PASSWORD "securePassword1"

void test_setup_table_entry() {
  // Setup - ensure clean state
  FILE *file = fopen(TEST_FILE_PATH, "r");
  if (file != NULL) {
    fclose(file);
    assert(remove(TEST_FILE_PATH) == 0);
  }

  // Create a new database file
  file = fopen(TEST_FILE_PATH, "w");
  assert(file != NULL);
  fclose(file);

  // Create database ()
  t_encrypted_database *enc_db = database_from_path(TEST_FILE_PATH);
  assert(enc_db != NULL);
  assert(enc_db->sql3p_database != NULL);

  // Decrypt with decrypt_database()
  t_decrypted_database *dec_db = decrypt_database(enc_db, TEST_PASSWORD);
  assert(dec_db != NULL);
  assert(dec_db->sql3p_database != NULL);

  // Test
  // Create test table
  int rc = setup_table_entry(dec_db);
  assert(rc == SQLITE_OK);

  // Insert test data
  const char *insert_sql =
      "INSERT INTO entry (title, user_name, password, is_deleted) VALUES "
      "('Test Entry 1', 'user1', 'passwd1', 0), "
      "('Test Entry 2', 'user2', 'passwd2', 1), "
      "('Test Entry 3', 'user3', 'passwd3', 0);";
  rc = sqlite3_exec(dec_db->sql3p_database, insert_sql, NULL, NULL, NULL);
  assert(rc == SQLITE_OK);

  // Verify data was inserted correctly
  sqlite3_stmt *stmt;
  const char *verify_sql = "SELECT COUNT(*) FROM entry;";
  rc = sqlite3_prepare_v2(dec_db->sql3p_database, verify_sql, -1, &stmt, NULL);
  assert(rc == SQLITE_OK);

  rc = sqlite3_step(stmt);
  assert(rc == SQLITE_ROW);
  int count = sqlite3_column_int(stmt, 0);
  assert(count == 3);
  sqlite3_finalize(stmt);

  // Verify specific data
  const char *select_sql =
      "SELECT name, password, is_deleted FROM entry ORDER BY id;";
  rc = sqlite3_prepare_v2(dec_db->sql3p_database, select_sql, -1, &stmt, NULL);
  assert(rc == SQLITE_OK);

  // Check first record
  rc = sqlite3_step(stmt);
  assert(rc == SQLITE_ROW);
  const char *name1 = (const char *)sqlite3_column_text(stmt, 0);
  const char *password1 = (const char *)sqlite3_column_text(stmt, 1);
  int is_deleted1 = sqlite3_column_int(stmt, 2);
  assert(strcmp(name1, "Test Entry 1") == 0);
  assert(strcmp(password1, "passwd1") == 0);
  assert(is_deleted1 == 0);

  // cleanup
  // Close with close_decrypted_database()
  int close_result = close_decrypted_database(dec_db);
  assert(close_result == 0);
  assert(dec_db->sql3p_database == NULL);

  free(dec_db);

  // Remove test file
  file = fopen(TEST_FILE_PATH, "r");
  if (file != NULL) {
    fclose(file);
    assert(remove(TEST_FILE_PATH) == 0);
  }

  printf("test_setup_table_entry passed\n");
}

int main() {
  printf("Running test_setup_table_entry...\n");
  test_setup_table_entry();
  printf("test_setup_table_entry passed successfully!\n");
  return 0;
}
