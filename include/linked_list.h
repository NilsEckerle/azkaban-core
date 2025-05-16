#ifndef LINKED_LIST_H
#define ENTRY_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @struct stLinkedListNode
 * @brief Linked list node for Entry structures.
 */
typedef struct stLinkedListNode {
  void* pData;        /**< Entry pData. */
	struct stLinkedListNode *pNext; /**< Pointer to the next node. */
} stLinkedListNode;

/**
 * @brief Initializes an list.
 * @param pData - pointer to pData
 * @return - Pointer to the pHead of the list if successful - NULL otherwise
 */
stLinkedListNode *fnLinkedListInit(void *pData);

/**
 * @brief Prepends an item to the list.
 * @param pHead - Pointer to the pHead of the list.
 * @param pData - pointer to pData
 * @return - 0 if successful - otherwise 1
 */
int fnLinkedListPrependNode(stLinkedListNode **pHead, void* pData);

/**
 * @brief append an item to the list.
 * @param pHead - Pointer to the pHead of the list.
 * @param pData - pointer to pData
 * @return - 0 if successful - otherwise 1
 */
int fnLinkedListAppendNode(stLinkedListNode **pHead, void* pData);

/**
 * @brief Gets the length of the list.
 * @param pHead - Pointer to the pHead of the list.
 * @return - Length of the list.
 */
int fnLinkedListGetLength(stLinkedListNode *pHead);

/**
 * @brief remove a the i-th element in the list while preserving linked list conectivity, counting starts at 0.
 * this doesnt free the pData.
 * @param pHead - Pointer to the pHead of the list.
 * @param index - the element at this location is deleted
 * @return - 0 if successful - 1 if index is out of range- otherwise 2
 */
int fnLinkedListRemoveNode(stLinkedListNode **pHead, unsigned int index);

/**
 * @brief Iterates over the list and applies a callback function to each entry.
 * @param pHead - Pointer to the pHead of the list.
 * @param fnpCallback - Callback function to apply.
 * @param pParameterGivenToCallback - Additional parameter for the callback.
 */
void fnLinkedListItterateFunction(stLinkedListNode *pHead,
											 void *fnpCallback(void *pParameter, void* pData),
											 void *pParameterGivenToCallback);

#endif
