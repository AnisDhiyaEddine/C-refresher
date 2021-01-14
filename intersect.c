#include "intersect.h"
#include "City.h"
#include <string.h>
int compareCities(const void *city1, const void *city2);
int compareCities(const void *city1 , const void *city2){
    City *c1 = (City *)city1;
    City *c2 = (City *)city2;

    if(c1->latitude != c2->latitude) return 0;
    if(c1->longitude != c2->longitude) return 0;
    if(strcmp(c1->name,c2->name) != 0) return 0;
    return 1;

}

LinkedList* intersect(const LinkedList* listA, const LinkedList* listB,
                      int comparison_fn_t(const void *, const void *)){
                          LLNode *head1 = listA->head;
                          LLNode *head2 = NULL;
                          LinkedList *result = newLinkedList();
                          while(head1 != NULL){
                              head2 = listB->head;
                              while(head2 != NULL){
                                  if(comparison_fn_t(head1->value , head2->value)){
                                      insertInLinkedList(result,head1->value);
                                  }
                                  head2 = head2->next;
                              }
                              head1 = head1->next;
                          }        
                          return result;        
                      }