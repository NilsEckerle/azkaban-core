#include "database.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_fnDdatabaseFromPath() {
	stDecryptedDatabase *stDecryptedDb = test_fnDdatabaseFromPath("test/test.db");
	assert(

  printf("test_fnLinkedListAppendNode passed\n");
}

int main() {
  printf("Running test_fnLinkedListAppendNode...\n");
  test_fnDdatabaseFromPath();
  printf("test_fnLinkedListAppendNode passed successfully!\n");
  return 0;
}
