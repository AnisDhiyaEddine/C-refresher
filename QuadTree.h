#ifndef _QUAD_TREE_H
#define _QUAD_TREE_H

#include <stddef.h>
#include <stdbool.h>
#include "LinkedList.h"
#include "City.h"

typedef struct _tree *QuadTree;
typedef struct cle *Cle;
typedef struct node *Node;


Cle newKey(double longitue, double latitude);

QuadTree fillQuad(LinkedList *list);

Node freeNode(Node root);

Node createNode(Cle key, City *value);

int compareKey(Cle key1, Cle key2);

void freeQuadTree(QuadTree tree);

size_t sizeOfQuadTree(Node root);

bool insertInQuadTree(QuadTree, City *value);

City *searchQuadTree(QuadTree, Cle key);

bool isInRage(Node nd, Cle keyMin, Cle keyMax);

void getInRage(Node node, LinkedList *list, Cle keyMin, Cle keyMax);

LinkedList *getInBox(QuadTree tree, Cle keyMin, Cle keyMax);

QuadTree newQuadTree();

#endif // !_QUAD_TREE_H_