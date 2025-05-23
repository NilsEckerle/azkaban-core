#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_linked_list_pop() {
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
	t_linked_list_node *tmp1 = linked_list_pop(&tp_ll_head, 0);
	t_linked_list_node *tmp2 = linked_list_pop(&tp_ll_head, 1);
	t_linked_list_node *tmp3 = linked_list_pop(&tp_ll_head, 13);
	assert(tmp1->vp_data == ip_data_1);
	assert(tmp2->vp_data == ip_data_3);
	assert(tmp3 == NULL);
	assert(tp_ll_head->vp_data == ip_data_2);
	assert(tp_ll_head->stp_ll_next->vp_data == ip_data_4);

	// cleanup
  free(ip_data_1);
  free(ip_data_2);
  free(ip_data_3);
  free(ip_data_4);
  free(tmp1);
  free(tmp2);
  free(tp_ll_head->stp_ll_next);
  free(tp_ll_head);

  printf("test_linked_list_pop passed\n");
}

int main() {
  printf("Running test_linked_list_pop...\n");
  test_linked_list_pop();
  printf("test_linked_list_pop passed successfully!\n");
  return 0;
}
