#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h> // fork et kill
#include <unistd.h> // fork et sleep
#include <signal.h> // signal


void fonction(int parametre){
  printf("Diantre, je meurs\n");
  exit(0);
}


int main(){

  pid_t fils = fork();

  if(fils == 0){ // Processus enfant
    signal(SIGINT, fonction);
    while(1){
      printf("J'ai pas peur\n");
    }
  }else{ //Processus parent
    printf("Attends un peu que je te tue\n");
    sleep(1);    
    kill(fils, SIGINT);    
  }
  return EXIT_SUCCESS;
}
