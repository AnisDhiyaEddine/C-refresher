#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // fork et kill
#include <unistd.h>    // fork
#include <signal.h>    // fill
#include <string.h>


int main(int charc, char **argv)
{
  char messagePF[100];
  char messageFP[100];

  int PF[2], FP[2];
  if ((pipe(PF) == -1) || (pipe(FP) == -1))
  {
    perror("error while creating the tube");
    exit(EXIT_FAILURE);
  }
  pid_t fils = fork();


  if (fils == 0)
  {
    close(PF[1]);
    close(FP[0]);
    read(PF[0], messagePF, 100);
    printf("mon père écrit %s \n ",messagePF);
    sprintf(messageFP, "Bien reçu");
    write(FP[1], messageFP, 11 * sizeof(char));
    close(PF[0]);
    close(FP[1]);
  }
  else
  {
    close(PF[0]);
    close(FP[1]);
    sprintf(messagePF, "je suis le père");
    write(PF[1], messagePF, 17*sizeof(char));
    read(FP[0], messageFP, 100);
    if(messageFP == "Bien reçu"){
      kill(fils, SIGTERM);
    }
    close(PF[1]);
    close(FP[1]);
  }
  exit(EXIT_SUCCESS);
}
