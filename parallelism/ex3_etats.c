#include<stdio.h>
#include<stdlib.h>
#include<pthread.h> // commandes pthread

void * dis_moi_des_trucs(void * rien){ 
  char * x = (char *)malloc(sizeof(char)*11);

  printf("Dis moi un truc\n");
  scanf("%10s", x); 


  pthread_exit(x);
}

int main () {
  pthread_t th1;
  void * retour ;
  
  if(pthread_create(&th1, NULL, dis_moi_des_trucs, "1") < 0)
    return EXIT_FAILURE;

  pthread_join( th1, &retour);
  printf("Tu m'as dis: %s \n", (char *) retour);  
  free(retour);
  
  return EXIT_SUCCESS;
}

