#include "LinkedList.h"
#include "City.h"
#include <stdio.h>
#include <stdlib.h>
#include "QuadTree.h"


/*Structure de la cle*/
struct cle
{
  double latitude;
  double longitude;
};

/*Structure d'un node*/
struct node
{
  Cle key;
  City *value;
  Node northEst;
  Node northWest;
  Node southEst;
  Node southWest;
};

/*Structure de l'arbre*/
struct _tree
{
  struct node *root;
  int size;
};

/****** implimentation des fonction ******/

/*Création d'une clé*/
Cle newKey(double longitue, double latitude)
{
  Cle key = malloc(sizeof(struct cle));
  if (key == NULL)
  {
    perror("Allocation memoire impossible");
    exit(1);
  }
  key->latitude = latitude;
  key->longitude = longitue;
  return key;
}

/* Libération de la zone mémoire occupé par un noeud */
Node freeNode(Node root)
{
  if (root == NULL)
  {
    return NULL;
  }
  freeNode(root->northEst);
  freeNode(root->northWest);
  freeNode(root->southEst);
  freeNode(root->southWest);
  free(root->key);
  free(root->value);
  free(root);
  return NULL;
}

/*La création d'un noeud*/
Node createNode(Cle key, City *value)
{
  Node n = malloc(sizeof(struct node));
  if (n == NULL)
  {
    perror("Allocation impossible");
    exit(1);
  }
  n->key = key;
  n->value = value;
  n->northEst = NULL;
  n->northWest = NULL;
  n->southEst = NULL;
  n->southWest = NULL;
  return n;
}

/*Comparison de deux clés*/
int compareKey(Cle key1, Cle key2)
{

  if ((key1->latitude == key2->latitude) && (key1->longitude == key2->longitude))
    return 0;
    
  if ((key1->longitude >= key2->longitude) && (key1->latitude >= key2->latitude))
    return 1;

  if ((key1->longitude > key2->longitude) && !(key1->latitude > key2->latitude))
    return 2;

  if ((key1->longitude <= key2->longitude) && !(key1->latitude <= key2->latitude))
    return 3;

  if ((key1->longitude <= key2->longitude) && (key1->latitude <= key2->latitude))
    return 4;

  return 0;
}

/*Créer un nouveau arbre*/
QuadTree newQuadTree(){
  QuadTree qTree = malloc(sizeof(struct _tree));
  if (qTree == NULL)
  {
    perror("Allocation impossible!");
    exit(1);
  }
  qTree->root = NULL;
  qTree->size = 0;
  return qTree;
}

/*Liberer un arbre*/
void freeQuadTree(QuadTree tree)
{
  freeNode(tree->root);
  free(tree);
}

/*La taille d'un arbre (le nombre d'élément)*/
size_t sizeOfQuadTree(Node root)
{
  if (root == NULL)
    return 0;
  return sizeOfQuadTree(root->northEst) + sizeOfQuadTree(root->northWest) + sizeOfQuadTree(root->southEst) + sizeOfQuadTree(root->southWest) + 1;
}

/*Insertion d'un noeud*/
bool insertInQuadTree(QuadTree tree, City *value)
{

  Cle key = newKey(value->longitude, value->latitude);

  Node nd = createNode(key, value);

  Node x = tree->root;
  Node pere = NULL;

  while (x != NULL)
  {
    pere = x;
    switch (compareKey(key, x->key))
    {
    case 0:
      x = x->northEst;
      break;
    case 1:
      x = x->northEst;
      break;
    case 2:
      x = x->northWest;
      break;
    case 3:
      x = x->southEst;
      break;
    case 4:
      x = x->southWest;
      break;
    }
  }
  if (pere == NULL)
  { //l'arbre est vide
    tree->root = nd;
  }
  else
  {
    switch (compareKey(key, pere->key))
    {
    case 0:
      pere->northEst = nd;
      break;
    case 1:
      pere->northEst = nd;
      break;
    case 2:
      pere->northWest = nd;
      break;
    case 3:
      pere->southEst = nd;
      break;
    case 4:
      pere->southWest = nd;
      break;
    }
  }
  tree->size++;
  return true;
}

City *searchQuadTree(QuadTree tree, Cle key)
{
  Node x = tree->root;
  while (x != NULL)
  {
    switch (compareKey(key, x->key))
    {
    case 1:
      x = x->northEst;
      break;
    case 2:
      x = x->northWest;
      break;
    case 3:
      x = x->southEst;
      break;
    case 4:
      x = x->southWest;
      break;
    case 0:
      return x->value;
      //break;
    }
  }
  return NULL;
}

/*Tester si un noeud (City) se situe entre 2 clées (2 points)*/
bool isInRage(Node nd, Cle keyMin, Cle keyMax)
{
   if (nd == NULL)
    return false;
  if ((compareKey(nd->key, keyMin) == 0) || (compareKey(nd->key, keyMax) == 0))
    return true;

  if ((compareKey(nd->key, keyMin) == 1)  && (compareKey(nd->key, keyMax) == 4) )
    return true;

  return false; 
}

/*Insirer dans la list tout les noeuds (Cities) qui sont entre les deux clées*/
void getInRage(Node node, LinkedList *list, Cle keyMin, Cle keyMax)
{

  if (node == NULL)
    return;

  getInRage(node->northEst, list, keyMin, keyMax);
  getInRage(node->northWest, list, keyMin, keyMax);
  getInRage(node->southEst, list, keyMin, keyMax);
  getInRage(node->southWest, list, keyMin, keyMax);

  if (isInRage(node, keyMin, keyMax))
  {
    insertInLinkedList(list, node->value);
  }

  return;
}

/*Retourner une list des cities qui sont entre deux clées*/
LinkedList *getInBox(QuadTree tree, Cle keyMin, Cle keyMax)
{
  LinkedList *list = newLinkedList();

  getInRage(tree->root, list, keyMin, keyMax);
  return list;
}

/*Construire un arbre quaternaire à partir d'une list*/
QuadTree fillQuad(LinkedList *list)
{
  QuadTree tree = newQuadTree();
  LLNode *node = list->head;

  City *c;
  while (node != NULL)
  {
    c = (City *)node->value;
    insertInQuadTree(tree, c);
    node = node->next;
  }
  return tree;
}
