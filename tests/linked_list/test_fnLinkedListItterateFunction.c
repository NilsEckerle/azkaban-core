#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Create a helper callback function that adds numbers to a running sum
void *sum_callback(void *p_sum, void *vp_data) {
  int *pi_running_sum = (int *)p_sum;
  int *pi_value = (int *)vp_data;
  *pi_running_sum += *pi_value;
  return NULL; // Return value is not used in this implementation
}

// Create a callback that modifies the data
void *double_value_callback(void *p_unused, void *vp_data) {
  int *pi_value = (int *)vp_data;
  *pi_value *= 2;
  return NULL;
}

void test_linked_list_itterate_function() {
  // Set up test data
  int *ip_data_1 = malloc(sizeof(int));
  int *ip_data_2 = malloc(sizeof(int));
  int *ip_data_3 = malloc(sizeof(int));
  *ip_data_1 = 10;
  *ip_data_2 = 20;
  *ip_data_3 = 30;

  // Create linked list with test data
  t_linked_list_node *tp_ll_head = linked_list_init(ip_data_1);
  linked_list_append_node(&tp_ll_head, ip_data_2);
  linked_list_append_node(&tp_ll_head, ip_data_3);
    
  // Create parameter to pass to callback (our running sum)
  int i_running_sum = 0;
    
  // Run the function we're testing
  linked_list_itterate_function(tp_ll_head, sum_callback, &i_running_sum);
    
  // Verify the function worked as expected
  assert(i_running_sum == 60); // 10 + 20 + 30 = 60
    
  // Test with empty list
  int i_empty_sum = 0;
  linked_list_itterate_function(NULL, sum_callback, &i_empty_sum);
  assert(i_empty_sum == 0); // Should not change
    
  // Run the function with the modification callback
  linked_list_itterate_function(tp_ll_head, double_value_callback, NULL);
    
  // Verify the values were modified
  assert(*ip_data_1 == 20);  // 10 * 2
  assert(*ip_data_2 == 40);  // 20 * 2
  assert(*ip_data_3 == 60);  // 30 * 2
    
  // Clean up
  free(ip_data_1);
  free(ip_data_2);
  free(ip_data_3);
  free(tp_ll_head->stp_ll_next->stp_ll_next);
  free(tp_ll_head->stp_ll_next);
  free(tp_ll_head);
    
  printf("test_linked_list_itterate_function passed\n");
}

int main() {
  printf("Running test_linked_list_itterate_function...\n");
  test_linked_list_itterate_function();
  printf("test_linked_list_itterate_function passed successfully!\n");
  return 0;
}
