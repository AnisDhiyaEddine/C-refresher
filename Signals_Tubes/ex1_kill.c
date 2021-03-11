#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h> // fork et kill
#include <unistd.h> // fork
#include <signal.h> // fill




int main(){

  pid_t fils = fork();

  if(fils == 0){ // Processus enfant
    while(1){
      printf("J'ai pas peur\n");
    }
  }else{ //Processus parent infanticide
    printf("Attends un peu que je te tue\n");
    sleep(1);
    kill(fils, SIGKILL);    
  }
  return EXIT_SUCCESS;
}
