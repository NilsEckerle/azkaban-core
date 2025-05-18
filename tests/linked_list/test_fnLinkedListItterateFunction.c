#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
  printf("Running test_fnLinkedListItterateFunction...\n");
  test_fnLinkedListItterateFunction();
  printf("test_fnLinkedListItterateFunction passed successfully!\n");
  return 0;
}
