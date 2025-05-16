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

void test_fnLinkedListRemoveNode() {
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

  fnLinkedListRemoveNode(&pstHead, 2);

  assert(fnLinkedListGetLength(pstHead) == 3);
  assert(pstHead->pData == piData1);
  assert(pstHead->pNext->pData == piData2);
  assert(pstHead->pNext->pNext->pData == piData4);
  assert(pstHead->pNext->pNext->pNext == NULL);

  free(piData1);
  free(piData2);
  free(piData3);
  free(piData4);
  free(pstHead->pNext->pNext);
  free(pstHead->pNext);
  free(pstHead);

  printf("test_fnLinkedListRemoveNode passed\n");
}

// Create a helper callback function that adds numbers to a running sum
void *fnSumCallback(void *pSum, void *pData) {
  int *piRunningSum = (int *)pSum;
  int *piValue = (int *)pData;
  *piRunningSum += *piValue;
  return NULL; // Return value is not used in this implementation
}

// Create a callback that modifies the data
void *fnDoubleValueCallback(void *pUnused, void *pData) {
  int *piValue = (int *)pData;
  *piValue *= 2;
  return NULL;
}

void test_fnLinkedListItterateFunction() {
  // Set up test data
  int *piData1 = malloc(sizeof(int));
  int *piData2 = malloc(sizeof(int));
  int *piData3 = malloc(sizeof(int));
  *piData1 = 10;
  *piData2 = 20;
  *piData3 = 30;

  // Create linked list with test data
  stLinkedListNode *pstHead = fnLinkedListInit(piData1);
  fnLinkedListAppendNode(&pstHead, piData2);
  fnLinkedListAppendNode(&pstHead, piData3);
    
  // Create parameter to pass to callback (our running sum)
  int iRunningSum = 0;
    
  // Run the function we're testing
  fnLinkedListItterateFunction(pstHead, fnSumCallback, &iRunningSum);
    
  // Verify the function worked as expected
  assert(iRunningSum == 60); // 10 + 20 + 30 = 60
    
  // Test with empty list
  int iEmptySum = 0;
  fnLinkedListItterateFunction(NULL, fnSumCallback, &iEmptySum);
  assert(iEmptySum == 0); // Should not change
    
  // Run the function with the modification callback
  fnLinkedListItterateFunction(pstHead, fnDoubleValueCallback, NULL);
    
  // Verify the values were modified
  assert(*piData1 == 20);  // 10 * 2
  assert(*piData2 == 40);  // 20 * 2
  assert(*piData3 == 60);  // 30 * 2
    
  // Clean up
  free(piData1);
  free(piData2);
  free(piData3);
  free(pstHead->pNext->pNext);
  free(pstHead->pNext);
  free(pstHead);
    
  printf("test_fnLinkedListItterateFunction passed\n");
}

int main() {
  printf("Running tests...\n");

  test_fnLinkedListInit();
  test_fnLinkedListPrependNode();
  test_fnLinkedListAppendNode();
  test_fnLinkedListGetLength();
  test_fnLinkedListRemoveNode();
  test_fnLinkedListItterateFunction();

  printf("All tests passed!\n");
  return 0;
}
