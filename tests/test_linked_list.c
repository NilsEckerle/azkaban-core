#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_ll_init_node() {
  Node *node = ll_init_node(NULL);
  assert(node != NULL);

  int data = 12;
  node = ll_init_node(&data);

  free(node);
  printf("test_ll_init_node passed\n");
}

void test_ll_prepend_node() {
  // Start with empty list
  Node *head = NULL;

  // Test with NULL head pointer
  int rc = ll_prepend_node(NULL, NULL);
  assert(rc == 1); // Should fail

  // Test with NULL data
  rc = ll_prepend_node(&head, NULL);
  assert(rc == 1); // Should fail

  // Test prepend to NULL
  int data1 = 42;
  rc = ll_prepend_node(&head, &data1);
  assert(rc == 1); // Should fail

  head = ll_init_node(0);
  Node *old_head = head;
  // Test successful prepend to empty list
  int data2 = 42;
  rc = ll_prepend_node(&head, &data2);
  assert(rc == 0); // Should succeed
  assert(head != NULL);
  assert(head->data == &data2);
  assert(head->next == old_head);

  // Test prepend to non-empty list
  int data3 = 84;
  rc = ll_prepend_node(&head, &data3);
  assert(rc == 0); // Should succeed
  assert(head->data == &data3);
  assert(head->next != NULL);
  assert(head->next->data == &data2);

  // Clean up
  free(head->next->next);
  free(head->next);
  free(head);

  printf("test_ll_prepend_node passed\n");
}

void test_ll_append_node() {
  // Start with empty list
  Node *head = NULL;

  // Test with NULL head pointer
  int rc = ll_append_node(NULL, NULL);
  assert(rc == 1); // Should fail

  // Test with NULL data
  rc = ll_append_node(&head, NULL);
  assert(rc == 1); // Should fail

  // Test append to NULL
  int data1 = 42;
  rc = ll_append_node(&head, &data1);
  assert(rc == 1); // Should fail

  head = ll_init_node(0);
  assert(head->next == NULL);
  Node *old_head = head;

  // Test successful append to empty list
  int data2 = 42;
  rc = ll_append_node(&head, &data2);
  assert(rc == 0); // Should succeed
  assert(head == old_head);
  assert(head->next->data == &data2);
  assert(head->next->next == NULL);

  // Test prepend to non-empty list
  int data3 = 84;
  rc = ll_append_node(&head, &data3);
  assert(rc == 0); // Should succeed
  assert(head->next->data == &data2);
  assert(head->next->next->data == &data3);
  assert(head->next->next->next == NULL);

  // Clean up
  free(head->next->next);
  free(head->next);
  free(head);

  printf("test_ll_append_node passed\n");
}

void test_ll_get_length() {
  Node *head = NULL;
	assert(ll_get_length(head) == 0);

	int data1= 1;
	head = ll_init_node(&data1);
	assert(ll_get_length(head) == 1);

	int data2= 2;
	ll_prepend_node(&head, &data2);
	assert(ll_get_length(head) == 2);

  free(head->next->next);
  free(head->next);
  free(head);

  printf("test_ll_get_length passed\n");
}

void test_ll_remove_node() {
	int *data1 = malloc(sizeof(int));
	int *data2 = malloc(sizeof(int));
	int *data3 = malloc(sizeof(int));
	int *data4 = malloc(sizeof(int));
	*data1 = 1;
	*data2 = 2;
	*data3 = 3;
	*data4 = 4;
  Node *head = ll_init_node(&data1);
	ll_append_node(&head, &data2);
	ll_append_node(&head, &data3);
	ll_append_node(&head, &data4);

	ll_remove_node(&head, 2);

	assert(ll_get_length(head) == 3);
	assert(head->data == &data1);
	assert(head->next->data == &data2);
	assert(head->next->next->data == &data4);
	assert(head->next->next->next == NULL);

	free(data1);
	free(data2);
	free(data3);
	free(data4);
  free(head->next->next);
  free(head->next);
  free(head);

  printf("test_ll_remove_nod passed\n");
}

// Create a helper callback function that adds numbers to a running sum
void *sum_callback(void *sum, void *data) {
		int *running_sum = (int *)sum;
		int *value = (int *)data;
		*running_sum += *value;
		return NULL; // Return value is not used in this implementation
}

// Create a callback that modifies the data
void *double_value_callback(void *unused, void *data) {
		int *value = (int *)data;
		*value *= 2;
		return NULL;
}

void test_ll_itterate_function() {
    // Set up test data
    int *data1 = malloc(sizeof(int));
    int *data2 = malloc(sizeof(int));
    int *data3 = malloc(sizeof(int));
    *data1 = 10;
    *data2 = 20;
    *data3 = 30;

    // Create linked list with test data
    Node *head = ll_init_node(data1);
    ll_append_node(&head, data2);
    ll_append_node(&head, data3);
    
    // Create parameter to pass to callback (our running sum)
    int running_sum = 0;
    
    // Run the function we're testing
    ll_itterate_function(head, sum_callback, &running_sum);
    
    // Verify the function worked as expected
    assert(running_sum == 60); // 10 + 20 + 30 = 60
    
    // Test with empty list
    int empty_sum = 0;
    ll_itterate_function(NULL, sum_callback, &empty_sum);
    assert(empty_sum == 0); // Should not change
    
    // Run the function with the modification callback
    ll_itterate_function(head, double_value_callback, NULL);
    
    // Verify the values were modified
    assert(*data1 == 20);  // 10 * 2
    assert(*data2 == 40);  // 20 * 2
    assert(*data3 == 60);  // 30 * 2
    
    // Clean up
    free(data1);
    free(data2);
    free(data3);
    free(head->next->next);
    free(head->next);
    free(head);
    
    printf("test_ll_itterate_function passed\n");
}

int main() {
  printf("Running tests...\n");

  test_ll_init_node();
  test_ll_prepend_node();
  test_ll_append_node();
	test_ll_get_length();
	test_ll_remove_node();
	test_ll_itterate_function();

  printf("All tests passed!\n");
  return 0;
}
