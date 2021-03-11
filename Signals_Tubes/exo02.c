#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h> // fork et kill
#include <unistd.h> // fork
#include <signal.h> // fill


int signals = 0;

void signalCalc(){
  signals = signals+1;
}

void exitFunction(){
  printf("shutting down child\n");
  exit(EXIT_SUCCESS);
}


int main(int charc, char **argv){

  pid_t fils = fork();

  if(fils == 0){
    while(1){
      signal(SIGUSR2, exitFunction);
      kill(getppid(), SIGUSR1);
      sleep(1);
    }
  }
  else
  {
    while(1){
      signal(SIGUSR1, signalCalc);
      if (signals == 5)
      {
        printf("heyyy number reached\n");
        kill(fils, SIGUSR2);
        sleep(1);
        exit(EXIT_SUCCESS);
      }
    }

   
  }
}
