#include "QuadTree.h"
#include <stdio.h>
#include <stdlib.h>
#include "findCities.h"

LinkedList *findCities(LinkedList *cities,
                       double latitudeMin,
                       double latitudeMax,
                       double longitudeMin,
                       double longitudeMax){
  QuadTree tree = newQuadTree();

  tree = fillQuad(cities);
  //printf("La taille de l'arbre:%ld\n", sizeOfQuadTree(tree));
  Cle keyMin = newKey(longitudeMin, latitudeMin);
  Cle keyMax = newKey(longitudeMax, latitudeMax);
  return getInBox(tree, keyMin,keyMax);
}