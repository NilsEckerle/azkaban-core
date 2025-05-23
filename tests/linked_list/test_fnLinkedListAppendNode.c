#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_linked_list_append_node() {
  // Start with empty list
  t_linked_list_node *tp_ll_head = NULL;

  // Test with NULL head pointer
  int i_rc = linked_list_append_node(NULL, NULL);
  assert(i_rc == 1); // Should fail

  // Test with NULL data
  i_rc = linked_list_append_node(&tp_ll_head, NULL);
  assert(i_rc == 1); // Should fail

  // Test append to NULL
  int i_data1 = 42;
  i_rc = linked_list_append_node(&tp_ll_head, &i_data1);
  assert(i_rc == 1); // Should fail

  tp_ll_head = linked_list_init(0);
  assert(tp_ll_head->stp_ll_next == NULL);
  t_linked_list_node *tp_ll_old_head = tp_ll_head;

  // Test successful append to empty list
  int i_data2 = 42;
  i_rc = linked_list_append_node(&tp_ll_head, &i_data2);
  assert(i_rc == 0); // Should succeed
  assert(tp_ll_head == tp_ll_old_head);
  assert(tp_ll_head->stp_ll_next->vp_data == &i_data2);
  assert(tp_ll_head->stp_ll_next->stp_ll_next == NULL);

  // Test prepend to non-empty list
  int i_data3 = 84;
  i_rc = linked_list_append_node(&tp_ll_head, &i_data3);
  assert(i_rc == 0); // Should succeed
  assert(tp_ll_head->stp_ll_next->vp_data == &i_data2);
  assert(tp_ll_head->stp_ll_next->stp_ll_next->vp_data == &i_data3);
  assert(tp_ll_head->stp_ll_next->stp_ll_next->stp_ll_next == NULL);

  // Clean up
  free(tp_ll_head->stp_ll_next->stp_ll_next);
  free(tp_ll_head->stp_ll_next);
  free(tp_ll_head);

  printf("test_linked_list_append_node passed\n");
}

int main() {
  printf("Running test_linked_list_append_node...\n");
  test_linked_list_append_node();
  printf("test_linked_list_append_node passed successfully!\n");
  return 0;
}
