// this is completely created by claude sonnet 4
// i read over it and don't see an issue
#include "database.h"
#include "sqlite3.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_FILE_PATH "unit_testing_workflow_database.azk"
#define TEST_PASSWORD "SecurePassword123"

void test_complete_workflow() {
    printf("Starting complete workflow test...\n");
    
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

    // STEP 1: Create database with database_from_path()
    printf("Step 1: Opening database from path...\n");
    t_encrypted_database *enc_db = database_from_path(TEST_FILE_PATH);
    assert(enc_db != NULL);
    assert(enc_db->sql3p_database != NULL);
    printf("✓ Database opened successfully\n");

    // STEP 2: Decrypt with decrypt_database()
    printf("Step 2: Decrypting database...\n");
    t_decrypted_database *dec_db = decrypt_database(enc_db, TEST_PASSWORD);
    assert(dec_db != NULL);
    assert(dec_db->sql3p_database != NULL);
    printf("✓ Database decrypted successfully\n");

    // STEP 3: Add data to decrypted database
    printf("Step 3: Adding test data...\n");
    
    // Create test table
    const char *create_table_sql = 
        "CREATE TABLE workflow_test ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "secret_data TEXT NOT NULL, "
        "number INTEGER"
        ");";
    int rc = sqlite3_exec(dec_db->sql3p_database, create_table_sql, NULL, NULL, NULL);
    assert(rc == SQLITE_OK);
    
    // Insert test data
    const char *insert_sql = 
        "INSERT INTO workflow_test (name, secret_data, number) VALUES "
        "('Test Entry 1', 'This is secret information!', 42), "
        "('Test Entry 2', 'Another secret message', 777), "
        "('Test Entry 3', 'Confidential data here', 999);";
    rc = sqlite3_exec(dec_db->sql3p_database, insert_sql, NULL, NULL, NULL);
    assert(rc == SQLITE_OK);
    
    // Verify data was inserted correctly
    sqlite3_stmt *stmt;
    const char *verify_sql = "SELECT COUNT(*) FROM workflow_test;";
    rc = sqlite3_prepare_v2(dec_db->sql3p_database, verify_sql, -1, &stmt, NULL);
    assert(rc == SQLITE_OK);
    
    rc = sqlite3_step(stmt);
    assert(rc == SQLITE_ROW);
    int count = sqlite3_column_int(stmt, 0);
    assert(count == 3);
    sqlite3_finalize(stmt);
    printf("✓ Test data added successfully (%d records)\n", count);

    // STEP 4: Close with close_decrypted_database() (encrypts data)
    printf("Step 4: Closing and encrypting database...\n");
    int close_result = close_decrypted_database(dec_db);
    assert(close_result == 0);
    assert(dec_db->sql3p_database == NULL);
    printf("✓ Database closed and encrypted\n");

    // STEP 5: Reopen and decrypt again
    printf("Step 5: Reopening and decrypting database...\n");
    t_encrypted_database *enc_db2 = database_from_path(TEST_FILE_PATH);
    assert(enc_db2 != NULL);
    assert(enc_db2->sql3p_database != NULL);
    
    t_decrypted_database *dec_db2 = decrypt_database(enc_db2, TEST_PASSWORD);
    assert(dec_db2 != NULL);
    assert(dec_db2->sql3p_database != NULL);
    printf("✓ Database reopened and decrypted successfully\n");

    // STEP 6: Verify data is still there and accessible
    printf("Step 6: Verifying data persistence...\n");
    
    // Check record count
    rc = sqlite3_prepare_v2(dec_db2->sql3p_database, verify_sql, -1, &stmt, NULL);
    assert(rc == SQLITE_OK);
    rc = sqlite3_step(stmt);
    assert(rc == SQLITE_ROW);
    count = sqlite3_column_int(stmt, 0);
    assert(count == 3);
    sqlite3_finalize(stmt);
    
    // Verify specific data
    const char *select_sql = "SELECT name, secret_data, number FROM workflow_test ORDER BY id;";
    rc = sqlite3_prepare_v2(dec_db2->sql3p_database, select_sql, -1, &stmt, NULL);
    assert(rc == SQLITE_OK);
    
    // Check first record
    rc = sqlite3_step(stmt);
    assert(rc == SQLITE_ROW);
    const char *name1 = (const char*)sqlite3_column_text(stmt, 0);
    const char *secret1 = (const char*)sqlite3_column_text(stmt, 1);
    int number1 = sqlite3_column_int(stmt, 2);
    assert(strcmp(name1, "Test Entry 1") == 0);
    assert(strcmp(secret1, "This is secret information!") == 0);
    assert(number1 == 42);
    
    // Check second record
    rc = sqlite3_step(stmt);
    assert(rc == SQLITE_ROW);
    const char *name2 = (const char*)sqlite3_column_text(stmt, 0);
    const char *secret2 = (const char*)sqlite3_column_text(stmt, 1);
    int number2 = sqlite3_column_int(stmt, 2);
    assert(strcmp(name2, "Test Entry 2") == 0);
    assert(strcmp(secret2, "Another secret message") == 0);
    assert(number2 == 777);
    
    // Check third record
    rc = sqlite3_step(stmt);
    assert(rc == SQLITE_ROW);
    const char *name3 = (const char*)sqlite3_column_text(stmt, 0);
    const char *secret3 = (const char*)sqlite3_column_text(stmt, 1);
    int number3 = sqlite3_column_int(stmt, 2);
    assert(strcmp(name3, "Test Entry 3") == 0);
    assert(strcmp(secret3, "Confidential data here") == 0);
    assert(number3 == 999);
    
    sqlite3_finalize(stmt);
    printf("✓ All data verified successfully after decryption\n");

    // STEP 7: Verify data is encrypted when accessed without decryption
    printf("Step 7: Verifying encryption security...\n");
    
    // Close the decrypted database first
    close_result = close_decrypted_database(dec_db2);
    assert(close_result == 0);
    
    // Try to access data with raw SQLite (should fail due to encryption)
    sqlite3 *raw_db;
    rc = sqlite3_open(TEST_FILE_PATH, &raw_db);
    assert(rc == SQLITE_OK);
    
    // Attempt to read encrypted data
    rc = sqlite3_prepare_v2(raw_db, select_sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        rc = sqlite3_step(stmt);
        // Should NOT be able to read the data without decryption
        assert(rc != SQLITE_ROW || sqlite3_column_text(stmt, 0) == NULL);
        sqlite3_finalize(stmt);
    }
    // If prepare failed, that's also good - means the database is encrypted
    
    sqlite3_close(raw_db);
    printf("✓ Data is properly encrypted when accessed without decryption\n");
    
    // Test wrong password (should fail)
    printf("Step 8: Testing wrong password security...\n");
    t_encrypted_database *enc_db3 = database_from_path(TEST_FILE_PATH);
    assert(enc_db3 != NULL);
    
    t_decrypted_database *dec_db_wrong = decrypt_database(enc_db3, "WrongPassword");
    assert(dec_db_wrong == NULL); // Should fail with wrong password
    
    // Clean up the failed attempt
    close_encrypted_database(enc_db3);
    free(enc_db3);
    printf("✓ Wrong password correctly rejected\n");

    // Final cleanup
    printf("Cleaning up...\n");
    free(dec_db);
    free(dec_db2);
    
    // Remove test file
    file = fopen(TEST_FILE_PATH, "r");
    if (file != NULL) {
        fclose(file);
        assert(remove(TEST_FILE_PATH) == 0);
    }
    
    printf("✓ Complete workflow test passed successfully!\n");
}

int main() {
    printf("Running complete database workflow test...\n");
    printf("=========================================\n");
    test_complete_workflow();
    printf("=========================================\n");
    printf("All workflow tests passed successfully!\n");
    return 0;
}
