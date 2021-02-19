#include<stdio.h>
#include<stdlib.h>
#include<pthread.h> // Threads spécific commands
#include<unistd.h> //Sleep Fork ... cmds

struct ID{
  long int value;
};

struct ID *createID(long int id);



void *function(void *);

int main(){
  pthread_t th[10]; // I konw how many threads i wanna create
  void *ret;
  long int i;

  for (i = 0; i < 10; i++){
    if (pthread_create(&th[i], NULL, function,(void *)createID(i)) < 0)
    {
      fprintf(stderr, "Thread creation error");
      return EXIT_FAILURE;
    }
  }

  for (i = 0; i < 10;i++){
    pthread_join(th[i], NULL);
  }
}

void *function(void *arg){
  struct ID *id = (struct ID *)arg;
  printf("The arg passed is %lu\n", id->value);
  pthread_exit(NULL);
}

struct ID *createID(long int id){
  struct ID *ID = malloc(sizeof(struct ID));
  ID->value = id;
  return ID;
}

//Concurence entre les thread ;)
//10 Thread essaye d'affiche le variable du boucle 