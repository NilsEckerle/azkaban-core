#include "linked_list.h"
#include <stdlib.h>

Node *ll_init_node(void) {
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {}

	node->data = NULL;
	node->next = NULL;

	return node;
}
