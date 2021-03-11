#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h> // fork et kill
#include <unistd.h> // fork et sleep
#include <signal.h> // signal




int main(){

  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);

  printf("Vas-y essaie de me tuer maintenant!!!");

  while(1);

  return EXIT_SUCCESS;
}
