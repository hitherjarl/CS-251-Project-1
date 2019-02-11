/*
 
 
 
 by Mohamed Imran Mohamed Siddique
 
 UIN:656951860
 
 E-mail: isiddi5@uic.edu
 
 
 
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct node {
    ElemType val;
    struct node *next;
} NODE;

struct list_struct {
    NODE *front;
    NODE *back;
    int count; //add whenever you push. subtract whenever you pop.
};

/*
 * returns pointer to newly created empty list
 */
LIST *lst_create() {
    LIST *l = malloc(sizeof(LIST));
    
    l->front = NULL;
    l->back = NULL;
    l->count = 0;
    return l;
}

void lst_free(LIST *l) {
    NODE *p = l->front;
    NODE *pnext;
    
    while(p != NULL) {
        pnext = p->next;   // keeps us from de-referencing a freed ptr
        free(p);
        p = pnext;
    }
    // now free the LIST
    free(l);
}

void lst_print(LIST *l) {
    NODE *p = l->front;
    
    printf("[");
    while(p != NULL) {
        printf(FORMAT, p->val);
        p = p->next;
    }
    printf("]\n");
}

//helper function->reverse order
void lst_print_rev_helper(NODE *p){
    
    if(!p)
        return;
    
    lst_print_rev_helper(p->next);
    printf(FORMAT, p->val);
}

/**
 * TODO:  print in reverse order
 *
 * Try to do without looking at notes!
 * Hints:  recursive helper function
 */
void lst_print_rev(LIST *l) {
    NODE *temp = l->front;
    
    printf("[");
    lst_print_rev_helper(temp); //call helper function
    printf("]\n");
}

void lst_push_front(LIST *l, ElemType val) {
    NODE *p = malloc(sizeof(NODE));
    
    p->val = val;
    p->next = l->front;
    
    l->front = p;
    if(l->back == NULL)
        l->back = p;
    (l->count)++;
}

void lst_push_back(LIST *l, ElemType val) {
    NODE *p;
    
    if(l->back == NULL){
        lst_push_front(l, val);
    }
    else {
        p = malloc(sizeof(NODE));
        p->val = val;
        p->next = NULL;
        l->back->next = p;
        
        l->back = p;
        (l->count)++;
    }
    
}

int lst_length(LIST *l) {
    return l->count;
    
}

int lst_is_empty(LIST *l) {
    if(l->front == NULL)
        return 1;
    return 0;
}


/** TODO
 *    function:  lst_count
 *     description:  Counts number of occurrences
 *     		of x in the list and returns
 *     		that value.
 */


int lst_count(LIST *l, ElemType x) {
    int count = 0;
    NODE *p = l->front;
    
    while(p != NULL) {
        if(p->val == x)
            count++;
        p = p->next;
    }
    
    return count;
}


/* These are "sanity checker" functions that check to see
 *     list invariants hold or not.
 */

int lst_sanity1(LIST *l) {
    if(l->front == NULL && l->back != NULL){
        fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
        return 0;
    }
    if(l->back == NULL && l->front != NULL){
        fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
        return 0;
    }
    return 1;
}

int lst_sanity2(LIST *l) {
    if(l->back != NULL && l->back->next != NULL) {
        fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
        return 0;
    }
    return 1;
}

/*
 *   makes sure that the back pointer is also the last reachable
 *    node when you start walking from front.
 *    HINT:  use pointer comparison
 */
int lst_sanity3(LIST *l) {
    
    
    printf("lst_sanity3 not implemented\n");
    
    
    return 1;
}

ElemType lst_pop_front(LIST *l) {
    ElemType ret;
    NODE *p;
    
    if(lst_is_empty(l))
        return DEFAULT;
    
    ret = l->front->val;
    
    if(l->front == l->back) {
        free(l->front);
        l->front = NULL;
        l->back = NULL;
    }
    else {
        p = l->front;
        l->front = l->front->next;
        free(p);
    }
    (l->count)--;
    return ret;
}

/* TODO
 *
 *    if list is empty, we do nothing and return arbitrary value
 *    otherwise, the last element in the list is removed and its
 *      value is returned.
 *
 */
ElemType lst_pop_back(LIST *l) {
    NODE *p = l->front;
    NODE *temp;
    int value;
    
    //empty
    if(lst_length(l) == 0){
        return -1;
    }
    //one on the list
    if(lst_length(l) == 1){
        value = l->front->val;
        l->front = NULL;
        l->back = NULL;
        (l->count)--;
        free(p);
        return value;
    }
    else{//more than one
        while(p->next->next != NULL){
            p = p->next;
        }
        value = p->val;
        l->back = p;
        l->back->next = NULL;
        free(p->next);
    }
    
    (l->count)--;
    
    return value;
}

/* TODO
 *  For full credit, you cannot allocate any new memory!
 *
 * description:  self-evident
 */
void lst_reverse(LIST *l) {
    NODE *current = l->front;
    NODE *previous = NULL;
    NODE *next = l->front;
    l->back = l->front;
    //for length of 0
    if(current == NULL)
        return;
    //for length of 1
    if(current->next == NULL){
        l->front->next = NULL;
        l->back->next = NULL;
        return;
    }
    //for length of > 1
    while(current != NULL){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    l->front = previous;
    l->back->next = NULL;
    
    
    return;
    
}


/*
 * removes first occurrence of x (if any).  Returns
 *   0 or 1 depending on whether x was found
 */
int lst_remove_first(LIST *l, ElemType x) {
    NODE *p;
    NODE *tmp;
    
    if(l->front == NULL)
        return 0;
    if(l->front->val == x) {
        lst_pop_front(l);
        return 1;
    }
    
    p = l->front;
    
    while(p->next != NULL) {
        if(x == p->next->val) {
            tmp = p->next;
            p->next = tmp->next;
            if(tmp == l->back)
                l->back = p;
            free(tmp);
            return 1;
        }
        p = p->next;
    }
    return 0;
}





int lst_remove_all_fast(LIST *l, ElemType x) {
    return 0;
}
//helper function for the sorting function
void swap(NODE *p1, NODE*p2)
{
    int temp = p1->val;
    p1->val = p2->val;
    p2->val = temp;
    
    
}

// TODO
int lst_is_sorted(LIST *l){
    
        NODE *start = l->front;
        NODE *traverse;
        NODE *min;
        
        while(start->next)
        {
            min = start;
            traverse = start->next;
            
            while(traverse)
            {
                
                if( min->val > traverse->val )
                {
                    min = traverse;
                }
                
                traverse = traverse->next;
            }
            swap(start,min);
            
            printf("%d ", start->val);
            start = start->next;
            
           
        }
    
    return 0;
   
    
}


/** TODO
 * function:  lst_insert_sorted
 *
 * description:  assumes given list is already in sorted order
 *	   and inserts x into the appropriate position
 * 	   retaining sorted-ness.
 * Note 1:  duplicates are allowed.
 *
 * Note 2:  if given list not sorted, behavior is undefined/implementation
 * 		dependent.  We blame the caller.
 * 		So... you don't need to check ahead of time if it is sorted.
 */
void lst_insert_sorted(LIST *l, ElemType x) {
    NODE *current = l->front;
    NODE *temp = (NODE *) malloc(sizeof(NODE));
    temp->val = x;
    
    
    if(lst_is_empty(l)){ //if list is empty
        lst_push_front(l, x);
        (l->count)++;
        return;
    }
    
    while(current != NULL){
                if(x <= l->front->val){
            l->front = temp;
            temp->next = current;
            (l->count)++;
            return;
        }
        
        
        if(x >= l->back->val){
            l->back->next = temp;
            l->back = temp;
            temp->next = NULL;
            (l->count)++;
            return;
        }
        
        
        if(x >= current->val && x < current->next->val){
            temp->next = current->next;
            current->next = temp;
            (l->count)++;
            return;
        }
        current = current->next;
    }
    return;
    
}

/** TODO
 * function:  lst_merge_sorted
 *
 * description:  assumes both list a and b are in
 * 	sorted (non-descending) order and merges them
 * 	into a single sorted list with the same
 * 	elements.
 *
 * 	This single sorted list is stored in a while
 * 	b becomes empty.
 *
 * 	if either of given lists are not sorted,
 * 	we blame the caller and the behavior is
 * 	implementation dependent -- i.e., don't worry
 * 	about it!
 *
 * 	Example:
 *
 * 		a:  [2 3 4 9 10 30]
 * 		b:  [5 8 8 11 20 40]
 *
 * 		after call on (a,b)
 *
 * 		a:  [2 3 4 5 8 8 9 10 11 20 30 40]
 * 		b:  []
 *
 * implementation:  should not allocate ANY new list
 * 	nodes -- it should just re-link existing
 * 	nodes.
 *
 * 	Must be linear time in the |a|+|b| -- i.e.,
 * 	the total number of elements being processed.
 */
void lst_merge_sorted(LIST *a, LIST *b){
    NODE *aCurrent = a->front;
    NODE *temp;
    //a empty
    if(b->front == NULL){
        return;
    }
    //a empty, b not empty
    if(a->front == NULL && b->front != NULL){
        if(b->front->next == NULL){
            a->front = b->front;
            a->back = b->back;
            b->front = NULL;
            b->back = NULL;
            
            return;
        }
    }
    
   
    
    else{
        while(b->front != NULL){
            //in front
            if(b->front->val < aCurrent->val){
                
                temp = b->front;
                b->front = b->front->next;
                
                temp->next = a->front;
                a->front = temp;
                
                (a->count)++;
                continue;
            }
            
            //in between
            if(b->front->val >= aCurrent->val && b->front->val < aCurrent->next->val){
                                temp = b->front;
                b->front = b->front->next;
                
                temp->next = aCurrent->next;
                aCurrent->next = temp;
                
                aCurrent = aCurrent->next;
                
                (a->count)++;
                continue;
            }
            //traverse
            aCurrent = aCurrent->next;
            if(aCurrent->val == a->back->val){
                
                break;
            }
        }
                aCurrent = a->back;
        while(b->front != NULL){
            
            temp = b->front;
            b->front = b->front->next;
            
            temp->next = aCurrent->next;
            aCurrent->next = temp;
            
            aCurrent = aCurrent->next;
            
            
            (a->count)++;
        }
        
    }
    
    b->front = NULL;
    b->back = NULL;
    
    return;
}

/**
 *
 * function:  lst_clone
 *
 * description:  makes a "deep copy" of the given list a
 *   and returns it (as a LIST pointer).
 *
 */
LIST * lst_clone(LIST *a) {
    LIST *ret = lst_create();
    NODE *temp = a->front;
    int i;
    
    
    if(lst_length(a) == 1){
        temp->val = a->front->val;
        lst_push_back(ret, temp->val);
        return ret;
    }
    
    for(i = 0; i <= lst_length(a) - 1; i++){
        lst_push_back(ret, temp->val);
        temp = temp->next;
    }
    
    
    return ret;
}



/**
 *
 * function:  lst_from_array
 *
 * description:  creates a new list populated with the
 *      elements of array a[] in the same order as
 *      they appear in a[] (element at a[0] will be the
 *      first element in the list and so-on).  List is
 *      returned as a LIST pointer.
 *
 *      Parameter n indicates the length of the given array.
 *
 * runtime requirement:  THETA(n)
 */
LIST * lst_from_array(ElemType a[], int n){
    LIST *ret = lst_create();
    int i;
    
    for(i = 0; i < n; i++){
        lst_push_back(ret, a[i]);
    }
    return ret;
    
}


/**
 *
 * function:  lst_to_array
 *
 * description:  allocates an array of ElemType and populates
 *         it with the elements in the given list (as with
 *         lst_from_array elements are in the same order in
 *         both data structures).
 *
 * runtime requirement:  THETA(n)
 *
 */
ElemType * lst_to_array(LIST *lst) {
    ElemType *arr = malloc(sizeof(ElemType) * lst_length(lst));
    NODE *temp = lst->front;
    int i = 0;
    
    while(temp != NULL){
        arr[i] = temp->val;
        temp = temp->next;
        i++;
    }
    
    return arr;
}


/**
 *
 * function:  lst_prefix
 *
 * description:  removes the first k elements from the
 *               given list which are used to form a new list
 *		which is then returned.
 *
 *		if n is the length of the given list, we have the
 *		following boundary conditions:
 *
 *		  if k==0:
 *			lst unchanged and an empty list returned
 *		  if k>=n:
 *			lst becomes empty and a list containing
 *			all elements previously in lst is returned.
 *
 *		examples:
 *
 *		  EX1:  lst:  [2, 3, 9, 7, 8]
 *			k:    3
 *
 *			after call:
 *			   lst:  [7, 8]
 *			   returned list:  [2, 3, 9]
 *
 *		  EX2  lst:  [2, 3, 9, 7, 8]
 *			k:    0
 *
 *			after call:
 *			   lst:  [2, 3, 9, 7, 8]  (unchanged)
 *			   returned list:  []
 *
 *		  EX3  lst:  [2, 3, 9, 7, 8]
 *			k:    5
 *
 *			after call:
 *			   lst:  []
 *			   returned list:  [2, 3, 9, 7, 8]
 *
 * REQUIREMENTS:
 *
 *	RUNTIME:  THETA(n) worst case where n is the length of the given list
 *
 *       ORDERING:  the ordering of the returned prefix should be the same as
 *                  in the given list
 *
 *       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
 *		   you should just "re-use" the existing nodes.  HOWEVER, you will
 *		   need to allocate a LIST structure itself (i.e., for the returned
 *		   list).
 */
LIST * lst_prefix(LIST *lst, unsigned int k) {
    LIST *ret = lst_create();
    NODE *temp = lst->front;
    int i = 0;
    if(k == 0){
        return ret;
    }
    if(k >= lst_length(lst)){
        while(temp != NULL){
            lst_push_back(ret, temp->val);
            temp = temp->next;
            i++;
        }
        return ret;
    }
    
    else{
        i = 0;
        while(i != k){
            lst_push_back(ret, temp->val);
            lst_pop_front(lst);
            temp = temp->next;
            i++;
        }
        return ret;
    }
    
    return ret;
    
}




/**
 *
 * function:  lst_filter_leq
 *
 * description:  removes all elements of the given list (lst) which
 *		are less than or equal to a given value (cutoff)
 *
 *		A list containing the removed elements is returned.
 *
 * examples:
 *
 *	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
 *		cutoff:  4
 *
 *		after call:
 *			lst:  [9, 8, 12, 7]
 *			returned list:  [4, 2, 4, 3]
 *
 *       -----------------------------------------
 *	EX2: 	lst:  [6, 5, 2, 1]
 *		cutoff:  6
 *
 *		after call:
 *			lst:  []
 *	 		returned list:  [6, 5, 2, 1]
 *
 * REQUIREMENTS:
 *
 *	RUNTIME:  THETA(n) where n is the length of the given list
 *
 *       ORDERING:  the ordering of the returned list should be the same as
 *                  in the given list
 *
 *       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
 *		   you should just "re-use" the existing nodes.  HOWEVER, you will
 *		   need to allocate a LIST structure itself (i.e., for the returned
 *		   list).
 *
 */
LIST * lst_filter_leq(LIST *lst, ElemType cutoff) {
    LIST *ret = lst_create();
    if(lst->front == NULL){
        return ret;
    }
    
    
    printf("Cutoff: %d\n", cutoff);
  
    NODE *temp = lst->front;
    int maxVal = temp->val;
    printf("MaxVal: %d\n", maxVal);
    
    
    //find max val
    while(temp != NULL){
        if(maxVal < temp->val){
            maxVal = temp->val;
        }
        temp = temp->next;
    }
    
    temp = lst->front;
    printf("MAXVALUE: %d\nCUTOFF: %d\n\n", maxVal, cutoff);
        if(cutoff >= maxVal){
        while(temp != NULL){
            lst_push_back(ret, temp->val);
            lst_pop_front(lst);
            temp = temp->next;
        }
    }
        else{
        while(temp != NULL){
            if(temp->val <= cutoff){
                lst_push_back(ret, temp->val);
                lst_pop_front(lst);
            }
            temp = temp->next;
        }
    }

    return ret;
    
}

/**
 * TODO
 * function:  lst_concat
 *
 * description:  concatenates lists a and b; resulting
 *    concatenation is reflected in list a; list b becomes
 *    empty.
 *
 *    example:
 *
 *	EX1:  a: [2, 9, 1]
 *	      b: [5, 1, 2]
 *
 *	after call:
 *
 *		a: [2, 9, 1, 5, 1, 2]
 *		b: []
 *
 * REQUIREMENTS:  
 *
 *     runtime:  O(1)
 *
 *     sanity:  this operation makes sense when a and b
 *		are distinct lists.  For example, we don't
 *		want/allow the caller to do something like
 *		this:
 *
 *			LIST *my_list;
 *
 *			lst_push_front(my_lst, 4);
 *			lst_push_front(my_lst, 2);
 *
 *			lst_concat(my_lst, my_lst);
 *
 *		your implementation must detect if it is being
 *		called this way.  If so the function does nothing
 *		and (optionally) prints an error message to
 *		stderr.
 *	
 */
void lst_concat(LIST *a, LIST *b) {
    
    
    //same list
    if(a == b){
        printf("\nerror\n");
        return;
    }
    
    //b empty
    if(lst_length(b) == 0){
        printf("empty");
        return;
    }
    //a empty not b
    if(lst_length(a) == 0 && lst_length(b) != 0){
        a->front = b->front;
        return;
    }
    
    //both not empty
    else{
        NODE *temp = a->front;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = b->front;
        a->back = b->back;
        b->front = NULL;
        b->back = NULL;
    }
    
    return;
}
