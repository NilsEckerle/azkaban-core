#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_linked_list_get() {
	// setup
  int *ivp_data_1 = malloc(sizeof(int));
  int *ivp_data_2 = malloc(sizeof(int));
  int *ivp_data_3 = malloc(sizeof(int));
  int *ivp_data_4 = malloc(sizeof(int));
  *ivp_data_1 = 1;
  *ivp_data_2 = 2;
  *ivp_data_3 = 3;
  *ivp_data_4 = 4;
  t_linked_list_node *tp_ll_head = linked_list_init(ivp_data_1);
  linked_list_append_node(&tp_ll_head, ivp_data_2);
  linked_list_append_node(&tp_ll_head, ivp_data_3);
  linked_list_append_node(&tp_ll_head, ivp_data_4);

	// test
	assert(linked_list_get(&tp_ll_head, 0)->vp_data == ivp_data_1);
	assert(linked_list_get(&tp_ll_head, 2)->vp_data == ivp_data_3);
	assert(linked_list_get(&tp_ll_head, 4) == NULL);

	// cleanup
  free(ivp_data_1);
  free(ivp_data_2);
  free(ivp_data_3);
  free(ivp_data_4);
  free(tp_ll_head->stp_ll_next->stp_ll_next->stp_ll_next);
  free(tp_ll_head->stp_ll_next->stp_ll_next);
  free(tp_ll_head->stp_ll_next);
  free(tp_ll_head);

  printf("test_linked_list_get passed\n");
}

int main() {
  printf("Running test_linked_list_get...\n");
  test_linked_list_get();
  printf("test_linked_list_get passed successfully!\n");
  return 0;
}
