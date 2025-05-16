#include "linked_list.h"
#include <stdlib.h>

stLinkedListNode *fnLinkedListInit(void *pData) {
  stLinkedListNode *pstNode = malloc(sizeof(stLinkedListNode));
  if (pstNode == NULL) {
    return NULL;
  }

  pstNode->pData = pData;
  pstNode->pNext = NULL;

  return pstNode;
}

int fnLinkedListPrependNode(stLinkedListNode **pstHead, void *pData) {
  if (pstHead == NULL) { return 1; }
  if (*pstHead == NULL) { return 1; }
  if (pData == NULL) { return 1; }

  stLinkedListNode *pstNewNode = fnLinkedListInit(pData);
  if (pstNewNode == NULL) { return 1; }

  // prepend node
  pstNewNode->pNext = *pstHead;
  *pstHead = pstNewNode;

  return 0;
}

int fnLinkedListAppendNode(stLinkedListNode **pstHead, void *pData) {
  if (pstHead == NULL) { return 1; }
  if (*pstHead == NULL) { return 1; }
  if (pData == NULL) { return 1; }

  stLinkedListNode *pstNewNode = fnLinkedListInit(pData);
  if (pstNewNode == NULL) { return 1; }

  // traverse til end of list
  stLinkedListNode *pstCurrent = *pstHead;
  while (pstCurrent->pNext != NULL) {
    pstCurrent = pstCurrent->pNext;
  }

  // append node
  pstCurrent->pNext = pstNewNode;

  return 0;
}

int fnLinkedListGetLength(stLinkedListNode *pstHead) {
  if (pstHead == NULL) { return 0; }

  int iLength = 1;
  stLinkedListNode *pstCurrent = pstHead;

  // traverse list til end
  while (pstCurrent->pNext != NULL) {
    iLength++;
    pstCurrent = pstCurrent->pNext;
  }

  return iLength;
}

int fnLinkedListRemoveNode(stLinkedListNode **pstHead, unsigned int uiIndex) {
  if (*pstHead == NULL) { return 1; }

  if (uiIndex == 0) {
    stLinkedListNode *pstTemp = *pstHead;
    *pstHead = (*pstHead)->pNext;

    free(pstTemp);

    return 0;
  }

  stLinkedListNode *pstCurrent = *pstHead;

  // Traverse to find the node just before the one to remove
  for (unsigned int i = 0; i < uiIndex - 1; i++) {
    if (pstCurrent->pNext == NULL) { return 1; } // Index out of bounds
    pstCurrent = pstCurrent->pNext;
  }
  
  // Check if we're trying to remove a node past the end
  if (pstCurrent->pNext == NULL) return 1;
  
  // Remove the pNext node (which is at position 'index')
  stLinkedListNode *pstTemp = pstCurrent->pNext;
  pstCurrent->pNext = pstTemp->pNext;

  free(pstTemp);

  return 0;
}

void fnLinkedListItterateFunction(stLinkedListNode *pstHead,
                      void *fnpCallback(void *pParameter, void* pData),
                      void *pParameterGivenToCallback) {
  stLinkedListNode *pstCurrent = pstHead;
  while (pstCurrent != NULL) {
    fnpCallback(pParameterGivenToCallback, pstCurrent->pData);
    pstCurrent = pstCurrent->pNext;
  }
}
