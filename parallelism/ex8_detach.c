#include<stdio.h>
#include<stdlib.h>
#include<pthread.h> // commandes pthread
#include <unistd.h> // sleep


void * fonction(void * args){
  printf("Coucou\n");
}



int main()
{
  pthread_t th1;
  void * retour ;

  if(pthread_create(&th1, NULL, fonction, NULL) < 0){
    fprintf(stderr, "pthread_create error for thread 1\n");
    exit(1);
  }

  /* Si on enlève cette ligne, il manquera un free à la fin du programme.
     Testez le programme avec `valgrind --leak-check=full`, avec et sans cette ligne.
  */
  pthread_detach(th1); 

  sleep(1);
  
  return EXIT_SUCCESS;
}
