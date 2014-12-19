#include <stdio.h>
#include "file_cache.h"
extern file_cache* head;

int main() {
 // /* unit test 1 
   const char *arr[2] = {"a1","b1"};
   file_cache_pin_files(head,arr,2);
 //  */
  
  /* unit test 2
   const char *arr[3] = {"a1","b1","a1"};
   file_cache_pin_files(head,arr,3);
  */

  /* unit test 3 
   file_cache_mutable_file_data(head,"a1");
  */
  
  /* unit test 4 
   const char *arr[1] = {"a1"};
   file_cache_mutable_file_data(head,"a1");
   file_cache_mutable_file_data(head,"a1");
  */
  /* unit test 5 
  
   const char *arr[2] = {"a1","b1"};
   file_cache_pin_files(head,arr,2);
   file_cache_mutable_file_data(head,"a1");
   const char *ar[1]={"a1"};
   file_cache_unpin_files(head,ar,1);
  */
   return 0;
}
