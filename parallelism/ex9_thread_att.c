#define _GNU_SOURCE // Obligatoire pour utiliser la fonction pthread_getattr_np
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h> // commandes pthread
#include<limits.h> // PTHREAD_STACK_MIN


void * fonction(void * args){
  pthread_attr_t attr;
  size_t taille;
  pthread_getattr_np(pthread_self(), &attr);
  pthread_attr_getstacksize(&attr, &taille);
  printf("Taille de la pile %lu dans le thread %lu\n", taille, pthread_self());
  pthread_attr_destroy(&attr);
  return args;
}

void initialiser_attributs(pthread_attr_t * attr){
  size_t taille;
  pthread_attr_init(attr);
  pthread_attr_getstacksize(attr, &taille);
  printf("Taille initiale de la pile %lu\n", taille);
  pthread_attr_setstacksize(attr, PTHREAD_STACK_MIN);
}

int main()
{
  pthread_t th1;
  pthread_attr_t attr;
  void * retour ;

  initialiser_attributs(&attr);
  if(pthread_create(&th1, &attr, fonction, NULL) < 0){
    fprintf(stderr, "pthread_create error for thread 1\n");
    exit(1);
  }

  pthread_join( th1, &retour);
  pthread_attr_destroy(&attr);
  return EXIT_SUCCESS;
}
