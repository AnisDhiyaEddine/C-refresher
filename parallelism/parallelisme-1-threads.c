#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void *function(void *argv)
{
  printf("running the program %s\n", ((char **)argv)[0]);
  if (execv(((char **)argv)[0], ((char **)argv)) < 0)
  {
    perror("Erreur of execv");
    exit(-1);
  }

  pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
  int i, n;
  pthread_t *tid;
  n = atoi(argv[1]);

  tid = (pthread_t *)malloc(n * sizeof(pthread_t));

  for (i = 0; i < n; i++)
  {
    if(pthread_create(&tid[i],NULL,function,argv+2)>0){
      perror("error creating the thread");
      exit(-1);
    }
    sleep(1);
  }

  pthread_exit(EXIT_SUCCESS);
}
