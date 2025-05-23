#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_linked_list_init() {
  t_linked_list_node *pst_node = linked_list_init(NULL);
  assert(pst_node != NULL);

  int i_data = 12;
  pst_node = linked_list_init(&i_data);

  free(pst_node);
  printf("test_linked_list_init passed\n");
}

int main() {
  printf("Running test_linked_list_init...\n");
  test_linked_list_init();
  printf("test_linked_list_init passed successfully!\n");
  return 0;
}
