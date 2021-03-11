#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h> // fork et kill
#include <unistd.h> // fork
#include <signal.h> // signal
#include <sys/wait.h> // wait

pid_t fils;

void meme_pas_peur(int signal_recu){
  printf("PISTOLERO 2: Même pas peur\n");
  kill(getppid(), SIGUSR2);
}

void esquiver(int signal_recu){
  printf("PISTOLERO 2: j'esquive tes balles!\n");
  exit(EXIT_SUCCESS);
}

void pan(int signal_recu){
  int status;
  printf("PISTOLERO 1: PAN !!!\n");
  kill(fils, SIGINT);
  wait(&status);

  if(WIFSIGNALED(status))
    printf("PISTOLERO 1: Je t'ai eu crapule\n");
  else
    printf("PISTOLERO 1: Diantre je l'ai raté!\n");    
  exit(EXIT_SUCCESS);
}

int main(){
  fils = fork();

  if(fils == 0){ // Processus enfant
    signal(SIGUSR1, meme_pas_peur);
    signal(SIGINT, esquiver);
    while(1);    
  }
  else{ //Processus parent
    signal(SIGUSR2, pan);
    printf("PISTOLERO 1: Attends un peu que je te tue\n");
    kill(fils, SIGUSR1);    
    while(1);
  }
  return EXIT_SUCCESS;
}
