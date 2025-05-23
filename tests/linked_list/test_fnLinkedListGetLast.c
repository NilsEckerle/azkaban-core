#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_linked_list_get_last() {
	// setup
  int *ip_data_1 = malloc(sizeof(int));
  int *ip_data_2 = malloc(sizeof(int));
  int *ip_data_3 = malloc(sizeof(int));
  int *ip_data_4 = malloc(sizeof(int));
  *ip_data_1 = 1;
  *ip_data_2 = 2;
  *ip_data_3 = 3;
  *ip_data_4 = 4;
  t_linked_list_node *tp_ll_head = linked_list_init(ip_data_1);
  linked_list_append_node(&tp_ll_head, ip_data_2);
  linked_list_append_node(&tp_ll_head, ip_data_3);
  linked_list_append_node(&tp_ll_head, ip_data_4);

	// test
	assert(linked_list_get_last(&tp_ll_head)->vp_data == ip_data_4);

	// cleanup
  free(ip_data_1);
  free(ip_data_2);
  free(ip_data_3);
  free(ip_data_4);
  free(tp_ll_head->stp_ll_next->stp_ll_next->stp_ll_next);
  free(tp_ll_head->stp_ll_next->stp_ll_next);
  free(tp_ll_head->stp_ll_next);
  free(tp_ll_head);

  printf("test_linked_list_get_last passed\n");
}

int main() {
  printf("Running test_linked_list_get_last...\n");
  test_linked_list_get_last();
  printf("test_linked_list_get_last passed successfully!\n");
  return 0;
}
