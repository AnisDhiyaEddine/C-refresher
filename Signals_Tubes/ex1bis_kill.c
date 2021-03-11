#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h> // fork et kill
#include <unistd.h> // fork
#include <signal.h> // fill

void bagheraa(){
  sleep(5);
  printf("Bagheraa dit: Réveille toi Mowgli !\n");
  kill(getppid(), SIGCONT);
}

void kaa(){
  printf("Kaa dit: Aie confiance  !\n");
  kill(getppid(), SIGTSTP);
}

int main(){
  int i;
  
  if(fork() == 0) // Processus Bagheraa
    bagheraa();
  else if(fork() == 0) // Processus Kaa
    kaa();
  else{
    for(i = 0; i < 1000000; i++);
    printf("Mowgli dit: Je me suis révéillé");
  }
    
  return EXIT_SUCCESS;
}
