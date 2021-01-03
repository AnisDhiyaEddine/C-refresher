#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "zscore.h"
#include "City.h"
#include <stdio.h>
#include <stdlib.h>


struct node{
    const void *key;
    const void *value;
    struct node *left;
    struct node *right;
    struct node *father;
}node;

struct tree_t{
struct node *root;
size_t size;
int (*compare)(const void*, const void*);
}tree_t;                              


//Utility functions 

int compareInt(const void* a,const void* b){

const uint64_t *varA = (const uint64_t *)a;
const uint64_t *varB = (const uint64_t *)b;
if(varA < varB){
 return -1;
}
if(varA == varB){
    return 0;
}
return 1;
}


int compareDouble(const void* a,const void* b){
const double varA = *(double*)a;
const double varB = *(double*)b;
if(varA < varB){
    return -1;
}
if(varA == varB){
    return 0;
}
return 1;
}


struct node* freeNode(struct node *root){
if(root == NULL){
    return NULL;
}
freeNode(root->left);
freeNode(root->right);
free(root);
return NULL;
}

struct node* createNode(const void *key,const void *value){
    struct node *n = malloc(sizeof(node));
    n->key = key;
    n->value = value;
    n->father = NULL;
    n->left = NULL;
    n->right = NULL;
    return n;
}


struct node* keyMinimalBST(struct node *root){
    struct node *x = root;
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}

struct node *getNode(BinarySearchTree *bst,const void *key){
struct node *node = keyMinimalBST(bst->root);
   while(bst->compare(node->key,key) < 0 && node != NULL){
       node = successorBST(node);
   }
   return node;
}

struct node *successorBST(struct node *node){
if(node->right != NULL){
    return keyMinimalBST(node->right);
}
struct node *n = node->father;
while(n != NULL && node == n->right){  
    node = n ;
    n = n->father;
}
return n;
}
 


////////////////////////////////////////////////////////////

BinarySearchTree* newBST(int comparison_fn_t(const void *, const void *)){
BinarySearchTree *bst = malloc(sizeof(BinarySearchTree));
bst->compare = comparison_fn_t;
bst->size = 0;
bst->root = NULL;
return bst;
}



void freeBST(BinarySearchTree* bst, bool freeContent){
    if(freeContent){
        freeNode(bst->root);
    }
    free(bst);
    return;
    }

size_t sizeOfBST(const BinarySearchTree* bst){
    return bst->size;
}


bool insertInBST(BinarySearchTree* tree, const void* key, const void* value){
struct node *n ,*x , *element;
element = createNode(key,value);
if(element == NULL) return false;
n = NULL;

x = tree->root;

while(x != NULL){
    n = x;

    if(tree->compare(key,x->key)<0){
        x = x->left;
           
    }else{
        x = x->right;
         
    }
}
    element->father = n;   //merging the key if it exists.
   
    if(n == NULL){
        // father of the element we want to insert is null so the tree is empty
        tree->root = element;
    }else{
        if(tree->compare(key,n->key) < 0){
            n->left = element;
        }else{
            n->right = element;
        }
    }
    tree->size++;
    return true;
}


 const void *searchRecursiveBST(BinarySearchTree *tree,struct node *root , const void *key){
 if(root != NULL){
    if((tree->compare(root->key,key)==0)){
        return root->value;
    }

    if(tree->compare(root->key,key)<0){
       return searchRecursiveBST(tree,root->right,key);
    }
    if(tree->compare(root->key,key)>0){
       return searchRecursiveBST(tree,root->left,key);
    }
}
return NULL;
} 

const void *searchBST(BinarySearchTree *tree,const void *key){
    return searchRecursiveBST(tree,tree->root,key);
}

LinkedList* getInRange(const BinarySearchTree* bst, void* keyMin, void* keyMax){

BinarySearchTree *tree = (BinarySearchTree *)bst;
LinkedList *list = newLinkedList();

struct node *temp = getNode(tree,keyMin);

if(temp == NULL) return NULL;
insertInLinkedList(list,temp->value);
temp = successorBST(temp);
 while(temp != NULL && tree->compare(temp->key,keyMax) <= 0){
    insertInLinkedList(list,temp->value);
    temp = successorBST(temp);
}  
return list;
}



const BinarySearchTree * fillBst(LinkedList *list, int comparison_fn_t(const void *, const void *) ,int flag)
{
    BinarySearchTree *tree = newBST(comparison_fn_t);
    LLNode *node = list->head;
    City  *c =NULL;
    if(flag == 0){
        // insert  key = lat
           const void *latitude;
        for(size_t i= 0; i < list->size; i++){
          c =(City *)node->value;
           latitude = &c->latitude; 
           insertInBST(tree,latitude,node->value);
            node =  node->next;
        }
    }
    if(flag == 1){
        // insert  key = long
           const void *longitude;
        for(size_t i= 0; i < list->size; i++){
          c =(City *)node->value;
           longitude = &c->longitude; 
           insertInBST(tree,longitude,node->value);
            node =  node->next;
        }
    }
    if(flag == 2){

        const void *zScore;
        uint64_t score;
        
        for(size_t i= 0; i < list->size; i++){
            c =(City *)node->value;
            score = zEncode(c->latitude,c->longitude);
    
            
            zScore =  (const void *)score;
        

         insertInBST(tree, zScore ,node->value);
            node =  node->next;


    }

    }
   
//printTree(tree->root);
return tree;
}

/*
void printTree(struct node *node){
if(node != NULL){

printTree(node->left);
printf("node : %d_\n",(uint64_t *)node->key);
printTree(node->right);
}
}

*/


