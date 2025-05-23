#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_linked_list_get_length() {
  t_linked_list_node *tp_ll_head = NULL;
  assert(linked_list_get_length(tp_ll_head) == 0);

  int i_data1 = 1;
  tp_ll_head = linked_list_init(&i_data1);
  assert(linked_list_get_length(tp_ll_head) == 1);

  int i_data2 = 2;
  linked_list_prepend_node(&tp_ll_head, &i_data2);
  assert(linked_list_get_length(tp_ll_head) == 2);

  free(tp_ll_head->stp_ll_next);
  free(tp_ll_head);

  printf("test_linked_list_get_length passed\n");
}

int main() {
  printf("Running test_linked_list_get_length...\n");
  test_linked_list_get_length();
  printf("test_linked_list_get_length passed successfully!\n");
  return 0;
}
