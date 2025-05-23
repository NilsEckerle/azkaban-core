#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_linked_list_remove_node() {
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

  linked_list_remove_node(&tp_ll_head, 2);

  assert(linked_list_get_length(tp_ll_head) == 3);
  assert(tp_ll_head->vp_data == ip_data_1);
  assert(tp_ll_head->stp_ll_next->vp_data == ip_data_2);
  assert(tp_ll_head->stp_ll_next->stp_ll_next->vp_data == ip_data_4);
  assert(tp_ll_head->stp_ll_next->stp_ll_next->stp_ll_next == NULL);

  free(ip_data_1);
  free(ip_data_2);
  free(ip_data_3);
  free(ip_data_4);
  free(tp_ll_head->stp_ll_next->stp_ll_next);
  free(tp_ll_head->stp_ll_next);
  free(tp_ll_head);

  printf("test_linked_list_remove_node passed\n");
}

int main() {
  printf("Running test_linked_list_remove_node...\n");
  test_linked_list_remove_node();
  printf("test_linked_list_remove_node passed successfully!\n");
  return 0;
}
