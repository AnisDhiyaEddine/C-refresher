#include "findCities.h"
#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "zscore.h"
#include "City.h"
#include <stdio.h>
#include <stdlib.h>



LinkedList* findCities(LinkedList* cities,
                       double latitudeMin,
                       double latitudeMax,
                       double longitudeMin,
                       double longitudeMax)
{
        const BinarySearchTree *bst = fillBst(cities,&compareDouble,2);
        printf("helloooo worldd");
/*         void *min = &latitudeMin; 
        void *max = &latitudeMax;
        LinkedList *s = getInRange(bst , min,max);

        LinkedList *list = newLinkedList();

         LLNode *n = s->head;
        City *c ;
 
    while(n != NULL){
     c = (City*) n->value;
     if(c->longitude <= longitudeMax && c->longitude >= longitudeMin) insertInLinkedList(list,n->value);
     n = n->next;
     }   */
return NULL;
}