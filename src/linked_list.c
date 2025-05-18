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

int fnLinkedListRemoveNode(stLinkedListNode **pstHead, int iIndex) {
  if (*pstHead == NULL) { return 1; }

  if (iIndex == 0) {
    stLinkedListNode *pstTemp = *pstHead;
    *pstHead = (*pstHead)->pNext;

    free(pstTemp);

    return 0;
  }

  stLinkedListNode *pstCurrent = *pstHead;

  // Traverse to find the node just before the one to remove
  for (int i = 0; i < iIndex - 1; i++) {
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

stLinkedListNode *fnLinkedListGet(stLinkedListNode **pHead, int iIndex) {
	stLinkedListNode *current = *pHead;

	// traverse list til index-th element
	for (int i = iIndex; i > 0; i--) {
		if (current == NULL) { return NULL; }
		current = current->pNext;
	}

	return current;
}

stLinkedListNode *fnLinkedListGetFirst(stLinkedListNode **pHead) {
	if (pHead == NULL) { return NULL; }
	return *pHead;
}

stLinkedListNode *fnLinkedListGetLast(stLinkedListNode **pHead) {
	if (pHead == NULL) { return NULL; }
	if (*pHead == NULL) { return NULL; }

	stLinkedListNode *current = *pHead;
	// traverse til end of list
	while (current->pNext != NULL) {
		current = current->pNext;
	}

	return current;
}

stLinkedListNode *fnLinkedListPop(stLinkedListNode **pHead, int iIndex) {
	if (pHead == NULL) { return NULL; }
	if (*pHead == NULL) { return NULL; }
	if (iIndex == 0) { 
		stLinkedListNode *target = *pHead;
		*pHead = target->pNext;
		target->pNext = NULL;
		return target;
	}

	stLinkedListNode *current = *pHead;
	// travwerse til (iIndex-1)-th position
	for (int i = iIndex - 1; i > 0; i--) {
		if (current == NULL) { return NULL; }
		current = current->pNext;
	}

	stLinkedListNode *target = current->pNext;
	if (target == NULL) { return NULL; }

	// cut target node from list
	current->pNext = target->pNext;
	target->pNext = NULL;

	return target;
}

stLinkedListNode *fnLinkedListPopFirst(stLinkedListNode **pHead) {
	if (pHead == NULL) { return NULL; }
	if (*pHead == NULL) { return NULL; }

	stLinkedListNode *target = *pHead;
	*pHead = target->pNext;
	target->pNext = NULL;

	return target;
}

stLinkedListNode *fnLinkedListPopLast(stLinkedListNode **pHead) {
	if (pHead == NULL) { return NULL; }
	if (*pHead == NULL) { return NULL; }
	if ((*pHead)->pNext == NULL) { 
		stLinkedListNode *target = *pHead;
		pHead = NULL;
		return target; 
	}

	stLinkedListNode *current = *pHead;
	// travwerse til end
	while (current->pNext->pNext != NULL) {
		current = current->pNext;
	}

	stLinkedListNode *target = current->pNext;
	current->pNext = NULL;

	return target;
}
