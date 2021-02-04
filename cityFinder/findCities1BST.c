#include "BinarySearchTree.h"
const BinarySearchTree *fillBst(LinkedList *list, int comparison_fn_t(const void *, const void *), int flag);
int compareDouble(const void *a, const void *b);
#include "findCities.h"
#include "LinkedList.h"
#include "zscore.c"
#include "City.h"
#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------------- *
 * Compare deux doubles.
 *
 * PARAMETERS
 * a   pointeur const void, le premier double à comparer
 * b   pointeur const void, le deuxième doubler à comparer
 * 
 * RETURN
 * -1  si (a < b)  
 *  0  si (a = b)
 *  1  sinon
 * ------------------------------------------------------------------------- */
int compareDouble(const void *a, const void *b)
{
        const double varA = *(double *)a;

        const double varB = *(double *)b;

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

LinkedList *findCities(LinkedList *cities,
                       double latitudeMin,
                       double latitudeMax,
                       double longitudeMin,
                       double longitudeMax)
{ //remplir l'arbre
        const BinarySearchTree *bst = fillBst(cities, &compareDouble, 0);

        void *min = &latitudeMin;

        void *max = &latitudeMax;

        //filtrer l'arbre
        LinkedList *s = getInRange(bst, min, max);

        //filtrage final
        if (s == NULL)
                return NULL;

        LinkedList *list = newLinkedList();

        LLNode *n = s->head;

        City *c;

        while (n != NULL)
        {

                c = (City *)n->value;

                if (c->longitude <= longitudeMax && c->longitude >= longitudeMin)
                        insertInLinkedList(list, n->value);

                n = n->next;
        }
        return list;
}