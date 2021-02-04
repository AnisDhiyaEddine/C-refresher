#include "BinarySearchTree.h"
const BinarySearchTree *fillBst(LinkedList *list, int comparison_fn_t(const void *, const void *), int flag);
int compareDouble(const void *a, const void *b);
int compareCities(const void *city1, const void *city2);

#include "intersect.h"
#include "findCities.h"
#include "LinkedList.h"
#include "zscore.c"
#include "City.h"
#include <stdio.h>
#include <stdlib.h>
/* ------------------------------------------------------------------------- *
 * Compare deux entiers (uint64_t).
 *
 * PARAMETERS
 * a   pointeur const void, le premier entier à comparer
 * b   pointeur const void, le deuxième entier à comparer
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
        const BinarySearchTree *bstLat = fillBst(cities, &compareDouble, 0);

        void *minLat = &latitudeMin;

        void *maxLat = &latitudeMax;

        //filtrer le premiere arbre
        LinkedList *listLat = getInRange(bstLat, minLat, maxLat);

        const BinarySearchTree *bstLng = fillBst(cities, &compareDouble, 1);

        void *minLng = &longitudeMin;

        void *maxLng = &longitudeMax;

        //filtrer le deuxieme arbre
        LinkedList *listLong = getInRange(bstLng, minLng, maxLng);

        //faire l'intersection des deux arbre
        LinkedList *list = intersect(listLat, listLong, compareCities);

        return list;
}