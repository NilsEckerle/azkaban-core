#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_fnLinkedListPopLast() {
	// setup
  int *piData1 = malloc(sizeof(int));
  int *piData2 = malloc(sizeof(int));
  int *piData3 = malloc(sizeof(int));
  int *piData4 = malloc(sizeof(int));
  *piData1 = 1;
  *piData2 = 2;
  *piData3 = 3;
  *piData4 = 4;
  stLinkedListNode *pstHead = fnLinkedListInit(piData1);
  fnLinkedListAppendNode(&pstHead, piData2);
  fnLinkedListAppendNode(&pstHead, piData3);
  fnLinkedListAppendNode(&pstHead, piData4);

	// test
	stLinkedListNode *tmp1 = fnLinkedListPopLast(&pstHead);
	assert(tmp1->pData == piData4);
	assert(pstHead->pData == piData1);
	assert(pstHead->pNext->pData == piData2);
	assert(pstHead->pNext->pNext->pData == piData3);

	// cleanup
  free(piData1);
  free(piData2);
  free(piData3);
  free(piData4);
  free(tmp1);
  free(pstHead->pNext->pNext);
  free(pstHead->pNext);
  free(pstHead);

  printf("test_fnLinkedListPopLast passed\n");
}

int main() {
  printf("Running test_fnLinkedListPopLast...\n");
  test_fnLinkedListPopLast();
  printf("test_fnLinkedListPopLast passed successfully!\n");
  return 0;
}
