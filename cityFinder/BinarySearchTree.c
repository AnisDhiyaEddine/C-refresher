#include "BinarySearchTree.h"
struct node *freeNode(struct node *root);
struct node *createNode(const void *key, const void *value);
const void *searchRecursiveBST(BinarySearchTree *tree, struct node *root, const void *key);
const BinarySearchTree *fillBst(LinkedList *list, int comparison_fn_t(const void *, const void *), int flag);
BinarySearchTree *newBST(int comparison_fn_t(const void *, const void *));
void getInRangeRec(const BinarySearchTree *bst, struct node *node, LinkedList *list, void *keyMin, void *keyMax);

void printTree(struct node *node);

#include "LinkedList.h"
#include "zscore.h"
#include "City.h"
#include <stdio.h>
#include <stdlib.h>

struct node
{

    const void *key;

    const void *value;

    struct node *left;

    struct node *right;

    struct node *father;
} node;

/*---------------------------------------------
* structure de notre arbre :
*
* root      un pointeur vers la racine de l'arbre 
* size      le nombre de noeud de l'arbre
* compare   la fonction de comparaison 
* 
------------------------------------------------*/
struct tree_t
{

    struct node *root;

    size_t size;

    int (*compare)(const void *, const void *);

} tree_t;

//--------------Utility functions---------------

/* ------------------------------------------------------------------------- *
 * Libere l'espace alloué par le noeud root et tous ses descendant.
 * fonction récursive.
 *
 * PARAMETERS
 * root  pointeur vers le noeud à libérer.
 * 
 * RETURN
 * NULL
 * ------------------------------------------------------------------------- */
struct node *freeNode(struct node *root)
{

    if (root == NULL)
    {

        return NULL;
    }
    freeNode(root->left);

    freeNode(root->right);

    free(root);

    return NULL;
}

/* ------------------------------------------------------------------------- *
 * Creer un noeud et initialiser sa clé et sa valeur avec les arguments 
 * passés en paramètre et les autres avec NULL.
 *
 * PARAMETERS
 * Key     pointeur const void, la clé 
 * value   pointeur const void, valeur (la ville)
 * 
 * RETURN
 * n  le noeud créé.
 * ------------------------------------------------------------------------- */
struct node *createNode(const void *key, const void *value)
{

    struct node *n = malloc(sizeof(node));

    n->key = key;

    n->value = value;

    n->father = NULL;

    n->left = NULL;

    n->right = NULL;

    return n;
}

/* ------------------------------------------------------------------------- *
 * fonction récursive qui filtre notre arbre et qui sera appeler dans la 
 * fonction getInRange (fonction de filtrage principale)
 *
 * PARAMETERS
 * bst    l'arbre à filtrer 
 * node   le noeud censé du filtrage 
 * list   la liste à remplir avec les valeurs filtré
 * keyMin la clé minimal 
 * KeyMax la clé maximal
 * 
 * RETURN
 * void
 * ------------------------------------------------------------------------- */
void getInRangeRec(const BinarySearchTree *bst, struct node *node, LinkedList *list, void *keyMin, void *keyMax)
{
    if (node == NULL)
    {
        return;
    }
    if ((bst->compare(node->key, keyMax) <= 0) && (bst->compare(node->key, keyMin) >= 0))
    {
        insertInLinkedList(list, node->value);
    }

    getInRangeRec(bst, node->left, list, keyMin, keyMax);

    getInRangeRec(bst, node->right, list, keyMin, keyMax);

    return;
}

////////////////////////////////////////////////////////////

/* ------------------------------------------------------------------------- *
 * Alloue un espace mémoire pour l'arbre et initialise ses attributs, et 
 * affecte la fonction de la comparaison à son attribut dans l'arbre. 
 * 
 * PARAMETERS
 * comparison_fn_t  la fonction de comparaison
 * 
 * RETURN
 * bst  l'arbre créé.
 * ------------------------------------------------------------------------- */
BinarySearchTree *newBST(int comparison_fn_t(const void *, const void *))
{

    BinarySearchTree *bst = malloc(sizeof(BinarySearchTree));

    bst->compare = comparison_fn_t;

    bst->size = 0;

    bst->root = NULL;

    return bst;
}

/* ------------------------------------------------------------------------- *
 * libère l'espace utilisé par l'arbre.
 * 
 * PARAMETERS
 * bst             pointeur vers l'arbre à libérer 
 * freeContent     boolean si vrai on commence par liberer les noeud avant
 *                 de liberer notre structure d'arbre faux sinon 
 * 
 * ------------------------------------------------------------------------- */
void freeBST(BinarySearchTree *bst, bool freeContent)
{
    if (freeContent)
    {

        freeNode(bst->root);
    }

    free(bst);
    return;
}

size_t sizeOfBST(const BinarySearchTree *bst)
{

    return bst->size;
}

/* ------------------------------------------------------------------------- *
 * inserer une nouvelle valeur "city" dans l'arbre selon la clé "key" 
 * 
 * PARAMETERS
 * tree    la racine de l'arbre
 * key     la clé pour pouvoir inserer
 * value   la valeur à inserer
 * 
 * RETURN
 * true.
 * ------------------------------------------------------------------------- */
bool insertInBST(BinarySearchTree *tree, const void *key, const void *value)
{

    struct node *n, *x, *element;

    element = createNode(key, value);

    if (element == NULL)
        return false;

    n = NULL;

    x = tree->root;

    while (x != NULL)
    {
        n = x;

        if (tree->compare(key, x->key) < 0)
        {

            x = x->left;
        }
        else
        {
            x = x->right;
            // If elements are equal we add in the right
        }
    }
    element->father = n; //merging the key if it exists.

    if (n == NULL)
    {
        // father of the element we want to insert is null so the tree is empty
        tree->root = element;
    }
    else
    {
        if (tree->compare(key, n->key) < 0)
        {

            n->left = element;
        }
        else
        {

            n->right = element;
        }
    }
    tree->size++;
    return true;
}

/* ------------------------------------------------------------------------- *
 * Recherche et renvoie la valeur "City" dont la clé "key" dans l'arbre "tree"
 * de manière récursive.
 * 
 * PARAMETERS
 * tree  pointeur vers la structure de l'arbre
 * root  la racine de l'arbre
 * key   la clé
 * 
 * RETURN
 * value  du noeud de la clé corressepondente.
 * si elle n'existe pas return null
 * ------------------------------------------------------------------------- */
const void *searchRecursiveBST(BinarySearchTree *tree, struct node *root, const void *key)
{
    if (root != NULL)
    {
        if ((tree->compare(root->key, key) == 0))
        {

            return root->value;
        }

        if (tree->compare(root->key, key) < 0)
        {

            return searchRecursiveBST(tree, root->right, key);
        }
        if (tree->compare(root->key, key) > 0)
        {

            return searchRecursiveBST(tree, root->left, key);
        }
    }
    return NULL;
}

/* ------------------------------------------------------------------------- *
 * recherche la valeur indexé par key en appelant la fonction récursive 
 * searchRecursiveBST
 * 
 * PARAMETERS
 * tree  pointeur vers la structure de l'arbre
 * key   la clé
 * 
 * RETURN
 * value  du noeud de la clé corressepondente.
 * si elle n'existe pas return null
 * ------------------------------------------------------------------------- */
const void *searchBST(BinarySearchTree *tree, const void *key)
{

    return searchRecursiveBST(tree, tree->root, key);
}

/* ------------------------------------------------------------------------- *
 * return une list contenant des valeurs "cities" des noeuds dont 
 * les clés sont entre "keyMin" et "keyMax"
 * 
 * PARAMETERS
 * bst      pointeur vers la structure de l'arbre     
 * keyMin   la clé min 
 * keyMax   la clé max
 * 
 * RETURN
 * list    la liste des values
 * ------------------------------------------------------------------------- */
LinkedList *getInRange(const BinarySearchTree *bst, void *keyMin, void *keyMax)
{

    BinarySearchTree *tree = (BinarySearchTree *)bst;

    LinkedList *list = newLinkedList();

    getInRangeRec(bst, tree->root, list, keyMin, keyMax);

    return list;
}

/* ------------------------------------------------------------------------- *
 * construire notre arbre selon l'approche spécifié par le flag à partir une
 * liste de villes.
 * 
 * PARAMETERS
 * list                 la liste des villes
 * comparison_fn_t      la fonction de comparison de l'apporche 
 * flag                 pour spécifier quel approche
 * 
 * 
 * RETURN
 * tree    pointeur vers notre arbre 
 * ------------------------------------------------------------------------- */
const BinarySearchTree *fillBst(LinkedList *list, int comparison_fn_t(const void *, const void *), int flag)
{
    BinarySearchTree *tree = newBST(comparison_fn_t);

    LLNode *node = list->head;

    City *c = NULL;

    if (flag == 0)
    {
        // insert  key = lat

        const void *latitude;

        for (size_t i = 0; i < list->size; i++)
        {

            c = (City *)node->value;

            latitude = &c->latitude;

            insertInBST(tree, latitude, node->value);

            node = node->next;
        }
    }
    if (flag == 1)
    {
        // insert  key = long

        const void *longitude;

        for (size_t i = 0; i < list->size; i++)
        {

            c = (City *)node->value;

            longitude = &c->longitude;

            insertInBST(tree, longitude, node->value);

            node = node->next;
        }
    }
    if (flag == 2)
    {

        const void *zScore;

        uint64_t score;

        for (size_t i = 0; i < list->size; i++)
        {

            c = (City *)node->value;

            score = zEncode(c->latitude, c->longitude);

            zScore = (const void *)score;

            insertInBST(tree, zScore, node->value);

            node = node->next;
        }
    }

    return tree;
}
