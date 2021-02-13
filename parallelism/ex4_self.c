#include<stdio.h>
#include<stdlib.h>
#include<pthread.h> // commandes pthread
#include <unistd.h> // sleep

void * fonction(void * args){
  printf("TID: %lu\n", pthread_self());
  return NULL;
}



int main()
{
  pthread_t th1;
  void * retour;

  printf("Taille d'un pthread_t: %lu  %lu\n", sizeof(pthread_t), sizeof(long unsigned int));

  if(pthread_create(&th1, NULL, fonction, NULL) < 0){
    fprintf(stderr, "pthread_create error for thread 1\n");
    exit(1);
  }

  pthread_join(th1, &retour);

  return EXIT_SUCCESS;
}
