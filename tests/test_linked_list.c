#include <stdio.h>
#include <assert.h>
#include "linked_list.h"


void test_ll_init_node() {
	Node *node = ll_init_node();
	assert(node->data == NULL);
	assert(node->next == NULL);
	printf("test_init passed\n");
}

int main() {
    printf("Running tests...\n");
    
    test_ll_init_node();
    
    printf("All tests passed!\n");
    return 0;
}
