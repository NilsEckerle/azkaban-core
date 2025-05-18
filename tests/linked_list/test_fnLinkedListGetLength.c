#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_fnLinkedListGetLength() {
  stLinkedListNode *pstHead = NULL;
  assert(fnLinkedListGetLength(pstHead) == 0);

  int iData1 = 1;
  pstHead = fnLinkedListInit(&iData1);
  assert(fnLinkedListGetLength(pstHead) == 1);

  int iData2 = 2;
  fnLinkedListPrependNode(&pstHead, &iData2);
  assert(fnLinkedListGetLength(pstHead) == 2);

  free(pstHead->pNext);
  free(pstHead);

  printf("test_fnLinkedListGetLength passed\n");
}

int main() {
  printf("Running test_fnLinkedListGetLength...\n");
  test_fnLinkedListGetLength();
  printf("test_fnLinkedListGetLength passed successfully!\n");
  return 0;
}
