#include "linked_list.h"
#include <stdlib.h>

Node *ll_init_node(void *data) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    return NULL;
  }

  node->data = data;
  node->next = NULL;

  return node;
}

int ll_prepend_node(Node **head, void *data) {
  if (head == NULL) { return 1; }
  if (*head == NULL) { return 1; }
  if (data == NULL) { return 1; }

  Node *new_node = ll_init_node(data);
  if (new_node == NULL) { return 1; }

  // prepend node
  new_node->next = *head;
  *head = new_node;

  return 0;
}

int ll_append_node(Node **head, void *data) {
  if (head == NULL) { return 1; }
  if (*head == NULL) { return 1; }
  if (data == NULL) { return 1; }

  Node *new_node = ll_init_node(data);
  if (new_node == NULL) { return 1; }

  // traverse til end of list
  Node *current = *head;
  while (current->next != NULL) {
    current = current->next;
  }

  // append node
  current->next = new_node;

  return 0;
}

int ll_get_length(Node *head) {
  if (head == NULL) { return 0; }

  int len = 1;
  Node *current = head;

  // traverse list til end
  while (current->next != NULL) {
    len++;
    current = current->next;
  }

  return len;
}

int ll_remove_node(Node **head, unsigned int index) {
	if (*head == NULL) { return 0; }

  if (index == 0) {
    Node *temp = *head;
    *head = (*head)->next;

    free(temp);

    return 0;
  }

  Node *current = *head;

	// Traverse to find the node just before the one to remove
  for (unsigned int i = 0; i < index - 1; i++) {
    if (current->next == NULL) { return 1; } // Index out of bounds
    current = current->next;
  }
  
  // Check if we're trying to remove a node past the end
  if (current->next == NULL) return 1;
  
  // Remove the next node (which is at position 'index')
  Node *temp = current->next;
  current->next = temp->next;

  free(temp);

  return 0;
}

void ll_itterate_function(Node *head,
                          void *callback(void *parameter, void *data),
                          void *parameter_given_to_callback) {
	Node *current = head;
	while (current != NULL) {
		callback(parameter_given_to_callback, current->data);
		current = current->next;
	}
}
