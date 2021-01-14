#include "BinarySearchTree.h"
const BinarySearchTree *fillBst(LinkedList *list, int comparison_fn_t(const void *, const void *), int flag);
int compareInt(const void *a, const void *b);
#include "findCities.h"
#include "LinkedList.h"
#include "zscore.h"
#include "City.h"
#include <stdio.h>
#include <stdlib.h>

    int compareInt(const void *a, const void *b)
{

    const uint64_t *varA = (const uint64_t *)a;
    const uint64_t *varB = (const uint64_t *)b;
    if (varA < varB)
    {
        return -1;
    }
    if (varA == varB)
    {
        return 0;
    }
    return 1;
}

LinkedList* findCities(LinkedList* cities,
                       double latitudeMin,
                       double latitudeMax,
                       double longitudeMin,
                       double longitudeMax)
{
        const BinarySearchTree *bst = fillBst(cities,&compareInt,2);

       void *min = (void *) zEncode(latitudeMin,longitudeMin);
        void *max = (void *) zEncode(latitudeMax,longitudeMax);

  

        LinkedList *s = getInRange(bst , min,max);

        LinkedList *list = newLinkedList();

         LLNode *n = s->head;
        City *c ;
 
    while(n != NULL){
     c = (City*) n->value;
     if(c->longitude <= longitudeMax && c->longitude >= longitudeMin 
     && c->latitude >= latitudeMin && c->latitude <= latitudeMax) insertInLinkedList(list,n->value);
     n = n->next;
     }
return list;
}



