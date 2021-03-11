#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h> // fork et kill
#include <unistd.h> // fork
#include <signal.h> // fill


int signals = 0;

void childHandler(){
  printf("child handler \n");
  signals = signals+1;
}

void exitFunction(){
    printf(" hey i'm shutting down \n");
    exit(EXIT_SUCCESS);
}


int main(int charc, char **argv){

  pid_t fils = fork();

  if(fils == 0){ 
      // Child process
  signal(SIGUSR2,exitFunction);
  while(1){
      kill(getppid(),SIGUSR1);
      sleep(2);
  }
  }else{ 
      // Parent process
    printf("Parent starts excuting\n");
    signal(SIGUSR1,childHandler);
    // hard coded value
    if(signals == 3)kill(fils,SIGUSR2);
  }

  printf("hello world");
  return EXIT_SUCCESS;
}
