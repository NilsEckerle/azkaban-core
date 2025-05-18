#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_fnLinkedListGet() {
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
	assert(fnLinkedListGet(&pstHead, 0)->pData == piData1);
	assert(fnLinkedListGet(&pstHead, 2)->pData == piData3);
	assert(fnLinkedListGet(&pstHead, 4) == NULL);

	// cleanup
  free(piData1);
  free(piData2);
  free(piData3);
  free(piData4);
  free(pstHead->pNext->pNext->pNext);
  free(pstHead->pNext->pNext);
  free(pstHead->pNext);
  free(pstHead);

  printf("test_fnLinkedListGet passed\n");
}

int main() {
  printf("Running test_fnLinkedListGet...\n");
  test_fnLinkedListGet();
  printf("test_fnLinkedListGet passed successfully!\n");
  return 0;
}
