#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_fnLinkedListPrependNode() {
  // Start with empty list
  stLinkedListNode *pstHead = NULL;

  // Test with NULL head pointer
  int iRc = fnLinkedListPrependNode(NULL, NULL);
  assert(iRc == 1); // Should fail

  // Test with NULL data
  iRc = fnLinkedListPrependNode(&pstHead, NULL);
  assert(iRc == 1); // Should fail

  // Test prepend to NULL
  int iData1 = 42;
  iRc = fnLinkedListPrependNode(&pstHead, &iData1);
  assert(iRc == 1); // Should fail

  pstHead = fnLinkedListInit(0);
  stLinkedListNode *pstOldHead = pstHead;
  // Test successful prepend to empty list
  int iData2 = 42;
  iRc = fnLinkedListPrependNode(&pstHead, &iData2);
  assert(iRc == 0); // Should succeed
  assert(pstHead != NULL);
  assert(pstHead->pData == &iData2);
  assert(pstHead->pNext == pstOldHead);

  // Test prepend to non-empty list
  int iData3 = 84;
  iRc = fnLinkedListPrependNode(&pstHead, &iData3);
  assert(iRc == 0); // Should succeed
  assert(pstHead->pData == &iData3);
  assert(pstHead->pNext != NULL);
  assert(pstHead->pNext->pData == &iData2);

  // Clean up
  free(pstHead->pNext->pNext);
  free(pstHead->pNext);
  free(pstHead);

  printf("test_fnLinkedListPrependNode passed\n");
}

int main() {
  printf("Running test_fnLinkedListPrependNode...\n");
  test_fnLinkedListPrependNode();
  printf("test_fnLinkedListPrependNode passed successfully!\n");
  return 0;
}
