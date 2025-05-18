#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_fnLinkedListPopFirst() {
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
	stLinkedListNode *tmp1 = fnLinkedListPopFirst(&pstHead);
	assert(tmp1->pData == piData1);
	assert(pstHead->pData == piData2);
	assert(pstHead->pNext->pData == piData3);
	assert(pstHead->pNext->pNext->pData == piData4);

	// cleanup
  free(piData1);
  free(piData2);
  free(piData3);
  free(piData4);
  free(tmp1);
  free(pstHead->pNext->pNext);
  free(pstHead->pNext);
  free(pstHead);

  printf("test_fnLinkedListPopFirst passed\n");
}

int main() {
  printf("Running test_fnLinkedListPopFirst...\n");
  test_fnLinkedListPopFirst();
  printf("test_fnLinkedListPopFirst passed successfully!\n");
  return 0;
}
