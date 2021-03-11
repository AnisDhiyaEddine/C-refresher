#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h> // fork et kill
#include <unistd.h> // fork
#include <signal.h> // fill

void function(){
    printf("Holaa called and wil terminate the child \n");
    exit(EXIT_SUCCESS);
}
int main(){

  pid_t fils = fork();

  if(fils == 0){ // Processus enfant
    signal(SIGINT,function);
    printf("Mon pid est %d \n",getpid());
    while(1){
      //printf("Le processus fils s'excute \n");
    }
  }else{ //Processus parent infanticide
    printf("Une seconde et je te tue\n");
    sleep(1);
    kill(fils, SIGINT);    
  }
  return EXIT_SUCCESS;
}
