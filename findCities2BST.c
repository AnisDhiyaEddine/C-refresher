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

LinkedList* findCities(LinkedList* cities,
                       double latitudeMin,
                       double latitudeMax,
                       double longitudeMin,
                       double longitudeMax)
{
        const BinarySearchTree *bstLat = fillBst(cities,&compareDouble,0);
        void *minLat = &latitudeMin; 
        void *maxLat = &latitudeMax;
        LinkedList *listLat = getInRange(bstLat , minLat,maxLat);

        const BinarySearchTree *bstLng = fillBst(cities,&compareDouble,1);
        void *minLng = &longitudeMin; 
        void *maxLng = &longitudeMax;
        LinkedList *listLong = getInRange(bstLng , minLng,maxLng);

        

        LinkedList *list = intersect(listLat,listLong,compareCities);

        
 

return list;
}