#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_fnLinkedListInit() {
  stLinkedListNode *pstNode = fnLinkedListInit(NULL);
  assert(pstNode != NULL);

  int iData = 12;
  pstNode = fnLinkedListInit(&iData);

  free(pstNode);
  printf("test_fnLinkedListInit passed\n");
}

int main() {
  printf("Running test_fnLinkedListInit...\n");
  test_fnLinkedListInit();
  printf("test_fnLinkedListInit passed successfully!\n");
  return 0;
}
