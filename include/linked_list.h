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
int fnLinkedListRemoveNode(stLinkedListNode **pHead, int index);

/**
 * @brief Iterates over the list and applies a callback function to each entry.
 * @param pHead - Pointer to the pHead of the list.
 * @param fnpCallback - Callback function to apply.
 * @param pParameterGivenToCallback - Additional parameter for the callback.
 */
void fnLinkedListItterateFunction(stLinkedListNode *pHead,
											 void *fnpCallback(void *pParameter, void* pData),
											 void *pParameterGivenToCallback);

/**
 * @brief Get node at position index (starting at 0)
 * @param pHead - Pointer to the head of the list.
 * @param iIndex - Index of the node to retrieve.
 * @return - Pointer to the node at the specified index, NULL if index is out of range.
 */
stLinkedListNode *fnLinkedListGet(stLinkedListNode **pHead, int iIndex);

/**
 * @brief Get first node in the list
 * @param pHead - Pointer to the head of the list.
 * @return - Pointer to the first node, NULL if list is empty.
 */
stLinkedListNode *fnLinkedListGetFirst(stLinkedListNode **pHead);

/**
 * @brief Get last node in the list
 * @param pHead - Pointer to the head of the list.
 * @return - Pointer to the last node, NULL if list is empty.
 */
stLinkedListNode *fnLinkedListGetLast(stLinkedListNode **pHead);

/**
 * @brief Remove and return the node at the specified index from the list (starting at 0)
 * @param pHead - Pointer to the head of the list.
 * @param iIndex - Index of the node to pop.
 * @return - Pointer to the removed node, NULL if index is out of range.
 */
stLinkedListNode *fnLinkedListPop(stLinkedListNode **pHead, int iIndex);

/**
 * @brief Remove and return the first node from the list
 * @param pHead - Pointer to the head of the list.
 * @return - Pointer to the removed first node, NULL if list is empty.
 */
stLinkedListNode *fnLinkedListPopFirst(stLinkedListNode **pHead);

/**
 * @brief Remove and return the last node from the list
 * @param pHead - Pointer to the head of the list.
 * @return - Pointer to the removed last node, NULL if list is empty.
 */
stLinkedListNode *fnLinkedListPopLast(stLinkedListNode **pHead);

#endif
