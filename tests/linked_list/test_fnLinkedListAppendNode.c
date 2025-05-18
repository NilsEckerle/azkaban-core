#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_fnLinkedListAppendNode() {
  // Start with empty list
  stLinkedListNode *pstHead = NULL;

  // Test with NULL head pointer
  int iRc = fnLinkedListAppendNode(NULL, NULL);
  assert(iRc == 1); // Should fail

  // Test with NULL data
  iRc = fnLinkedListAppendNode(&pstHead, NULL);
  assert(iRc == 1); // Should fail

  // Test append to NULL
  int iData1 = 42;
  iRc = fnLinkedListAppendNode(&pstHead, &iData1);
  assert(iRc == 1); // Should fail

  pstHead = fnLinkedListInit(0);
  assert(pstHead->pNext == NULL);
  stLinkedListNode *pstOldHead = pstHead;

  // Test successful append to empty list
  int iData2 = 42;
  iRc = fnLinkedListAppendNode(&pstHead, &iData2);
  assert(iRc == 0); // Should succeed
  assert(pstHead == pstOldHead);
  assert(pstHead->pNext->pData == &iData2);
  assert(pstHead->pNext->pNext == NULL);

  // Test prepend to non-empty list
  int iData3 = 84;
  iRc = fnLinkedListAppendNode(&pstHead, &iData3);
  assert(iRc == 0); // Should succeed
  assert(pstHead->pNext->pData == &iData2);
  assert(pstHead->pNext->pNext->pData == &iData3);
  assert(pstHead->pNext->pNext->pNext == NULL);

  // Clean up
  free(pstHead->pNext->pNext);
  free(pstHead->pNext);
  free(pstHead);

  printf("test_fnLinkedListAppendNode passed\n");
}

int main() {
  printf("Running test_fnLinkedListAppendNode...\n");
  test_fnLinkedListAppendNode();
  printf("test_fnLinkedListAppendNode passed successfully!\n");
  return 0;
}
