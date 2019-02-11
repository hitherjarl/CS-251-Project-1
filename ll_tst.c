
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <math.h>

// very incomplete small test program...

int main() {
    LIST *lst1;
    int i;
    
    lst1 = lst_create();
    
    
    for(i=0; i<5; i++) {
        lst_push_front(lst1, rand()%10);
    }
    
    for(i=0; i<5; i++) {
        lst_push_back(lst1, i);
    }
  
    
    
    /** test code for lst_print_rev **/
      lst_print(lst1);
    lst_is_sorted(lst1);
    
   
    
    
    
     LIST *lst2 = lst_create();
     for(i = 0; i < 5; i++){
     lst_push_back(lst2, i);
     }
     printf("\n\nLIST 2\n");
     lst_print(lst2);
     printf("\nList 2 Sorted: %d\n", lst_is_sorted(lst2));
     printf("Sanity 1: %d\nSanity 2: %d\n", lst_sanity1(lst2), lst_sanity2(lst2));
     
     
     //testing insert sort
     printf("\n\nTESTING INSERT SORTED\n");
     lst_print(lst2);
     printf("\nInserting 0 into list\n");
     lst_insert_sorted(lst2, 0);
     lst_print(lst2);
     
     printf("\nInserting 5 into list\n");
     lst_insert_sorted(lst2, 5);
     lst_print(lst2);
     
     printf("\nInserting 1 into list\n");
     lst_insert_sorted(lst2, 1);
     lst_print(lst2);
     
     
     printf("\nList 2 Sorted: %d\n", lst_is_sorted(lst2));
     printf("Sanity 1: %d\nSanity 2: %d\n", lst_sanity1(lst2), lst_sanity2(lst2));
    
    
    //testing merge sort
    
    LIST *lst3 = lst_create();
    LIST *lst4 = lst_create();
    for(i = 1; i < 10; i+=2)
        lst_push_back(lst3, i);
    for(i = 0; i <= 10; i+=2)
        lst_push_back(lst4, i);
    lst_insert_sorted(lst4, 6);
    
    lst_print(lst3);
    lst_print(lst4);
     
    printf("\nMERGE SORTING\n");
    lst_merge_sorted(lst3, lst4);
    
    lst_print(lst3);
    lst_print(lst4);
    

    printf("\n FILTER\n");
    LIST *lst8 = lst_create();
    
    lst_push_front(lst3, 10);
    lst_push_front(lst3, 20);
    lst_pop_back(lst3);
    
    lst_print(lst3);
    lst_print(lst8);
    
    lst8 = lst_filter_leq(lst3, 9);
    lst_print(lst3);
    lst_print(lst8);
    
   
    
    lst_free(lst1);
}

