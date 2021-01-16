#include <stdio.h>
#include <stdlib.h>
#include "findCities.h"
#include "QuadTree.h"

LinkedList *findCities(LinkedList *cities,
                       double latitudeMin,
                       double latitudeMax,
                       double longitudeMin,
                       double longitudeMax){
  QuadTree tree = newQuadTree();

  tree = fillQuad(cities);
  Cle keyMin = newKey(longitudeMin, latitudeMin);
  Cle keyMax = newKey(longitudeMax, latitudeMax);
  return getInBox(tree, keyMin,keyMax);
}