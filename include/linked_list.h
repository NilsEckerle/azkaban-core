#ifndef ENTRY_H
#define ENTRY_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @struct Node
 * @brief Linked list node for Entry structures.
 */
typedef struct Node {
  void* data;        /**< Entry data. */
	struct Node *next; /**< Pointer to the next node. */
} Node;

/**
 * @brief Initializes an list.
 * @return Pointer to the head of the list.
 */
Node *init(void);

/**
 * @brief Prepends an item to the list.
 * @param head - Pointer to the head of the list.
 * @param data - pointer to data
 * return - 0 if successful - otherwise 1
 */
int prepend(Node **head, void* data);

/**
 * @brief append an item to the list.
 * @param head - Pointer to the head of the list.
 * @param data - pointer to data
 * return - 0 if successful - otherwise 1
 */
int append(Node **head, void* data);

/**
 * @brief remove a the i-th element in the list while preserving linked list conectivity, counting starts at 0.
 * @param head - Pointer to the head of the list.
 * @param index - the element at this location is deleted
 * return - 0 if successful - 1 if index is out of range- otherwise 2
 */
int remove(Node **head, int index);

/**
 * @brief Iterates over the list and applies a callback function to each entry.
 * @param head - Pointer to the head of the list.
 * @param callback - Callback function to apply.
 * @param parameter_given_to_callback - Additional parameter for the callback.
 */
void itterate_function(Node *head,
											 void *callback(void *parameter, void* data),
											 void *parameter_given_to_callback);

/**
 * @brief Gets the length of the list.
 * @param head - Pointer to the head of the list.
 * @return - Length of the list.
 */
int entry_list_get_length(EntryNode *head);

#endif
