#include<stdio.h>
#include<stdlib.h>
#include<pthread.h> // commandes pthread
#include <unistd.h> // sleep

void * fonction(void * arg){
  long int id = (long int)arg;
  printf("Mon argument: %ld\n", id);
  pthread_exit(arg);
}


int main()
{
  pthread_t th[10];
  long int i;
  void * retour;

  printf("Taille d'un pthread_t: %lu  %lu\n", sizeof(pthread_t), sizeof(long unsigned int));

  for(i = 0; i < 10; i++){
      if(pthread_create(&th[i], NULL, fonction, (void *)i) < 0){
        fprintf(stderr, "pthread_create error for thread 1\n");
        exit(1);
      }
  }

  for(i = 0; i < 10; i++)
    pthread_join(th[i], &retour);

  return EXIT_SUCCESS;
}
