#include "findCities.h"
#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "intersect.h"
#include "zscore.c"
#include "City.h"
#include <stdio.h>
#include <stdlib.h>






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