#include<stdio.h>
#include<stdlib.h>
#include<pthread.h> // commandes pthread
#include <unistd.h> // sleep

typedef struct bidule_s{
    int truc;
    char machin;
} bidule_t;

bidule_t * creer_bidule(int t, char m){
    bidule_t * res = malloc(sizeof(bidule_t));
    res->truc = t;
    res->machin = m;
    return res;
}

void * fonction(void * arg){
  bidule_t * b = (bidule_t *)arg;
  printf("Mon Bidule: %d %c\n", b->truc, b->machin);
  pthread_exit(arg);
}


int main()
{
  pthread_t th[10];
  long int i;
  void * retour;

  printf("Taille d'un pthread_t: %lu  %lu\n", sizeof(pthread_t), sizeof(long unsigned int));

  for(i = 0; i < 10; i++){
      if(pthread_create(&th[i], NULL, fonction, creer_bidule(i,'a'+i)) < 0){
        fprintf(stderr, "pthread_create error for thread 1\n");
        exit(1);
      }
  }

  for(i = 0; i < 10; i++){
    pthread_join(th[i], &retour);
    free(retour);
  }

  return EXIT_SUCCESS;
}
